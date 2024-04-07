#include <Geode/modify/PlayLayer.hpp>
#include "../TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel *level, bool p1, bool p2) {
        if (!PlayLayer::init(level, p1, p2)) {
            return false;
        }

        TimeCounter::setLevel(level);
        TimeCounter::setStartTime();
        TimeCounter::setStartTimeNoPause();
        log::info("AttStart");

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        bool startpos = PlayLayer::get()->m_isTestMode;
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool prevstartpos = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isStartpos");
        bool prevnormal = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isNormal");
        if (startpos) {
            if (!prevstartpos) {
                log::info("startpos begin");
                TimeCounter::setStartTimeStartpos();
                Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", true);
            }
        }
        else {
            if (prevstartpos) {
                log::info("startpos end");
                TimeCounter::updateTotalTimeStartpos();
                Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
            }
        }
        if (!startpos && !practice) {
            if (!prevnormal) {
                log::info("normal begin");
                TimeCounter::setStartTimeNormal();
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", true);
            }
        }
        else {
            if (prevnormal) {
                log::info("normal end");
                TimeCounter::updateTotalTimeNormal();
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
            }
        }
    }

    void levelComplete() {
        PlayLayer::levelComplete();
        TimeCounter::updateTotalTimeNoPause();
        auto testmode = PlayLayer::get()->m_isTestMode;
    }

    void togglePracticeMode(bool p0) {
        PlayLayer::togglePracticeMode(p0);
        if (p0) {
            TimeCounter::setStartTimePractice();
            if (!PlayLayer::get()->m_isTestMode) {
                TimeCounter::updateTotalTimeNormal();
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
            }
        }
        else {
            TimeCounter::updateTotalTimePractice();
        }
    }

    void fullReset() {
        PlayLayer::fullReset();
        TimeCounter::setStartTimeNoPause();
    }

    void onQuit() {
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;
        if (practice) {TimeCounter::updateTotalTimePractice();}
        if (startpos) {TimeCounter::updateTotalTimeStartpos();}
        if (!practice && !startpos) {TimeCounter::updateTotalTimeNormal();}
        PlayLayer::onQuit();
        TimeCounter::updateTotalTime();
        Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);

        // log::info("{} attemptTime: {}", this->m_level->m_levelName, this->m_level->m_attemptTime.value());
        // log::info("{} workingTime: {}", this->m_level->m_levelName, this->m_level->m_workingTime);
        // log::info("{} workingTime2: {}", this->m_level->m_levelName, this->m_level->m_workingTime2);
        // logging
        auto name = TimeCounter::levelName;
        auto time = TimeCounter::getTotalTime();
        auto timenormal = TimeCounter::getTotalTimeNormal();
        auto timepractice = TimeCounter::getTotalTimePractice();
        auto timestartpos = TimeCounter::getTotalTimeStartpos();
        auto timenopause = TimeCounter::getTotalTimeNoPause();
        log::info("{}: {} with pauses", name, time);
        log::info("{}: {} normal", name, timenormal);
        log::info("{}: {} practice", name, timepractice);
        log::info("{}: {} startpos", name, timestartpos);
        log::info("{}: {} without pauses", name, timenopause);
    }

};