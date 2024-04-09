#include <Geode/modify/PlayLayer.hpp>
#include "TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel *level, bool p1, bool p2) {
        if (!PlayLayer::init(level, p1, p2)) {
            return false;
        }

        TimeCounter::setLevel(level);
        TimeCounter::setStartTime(CounterType::Total);
        TimeCounter::setStartTime(CounterType::NoPause);

        log::info("AttStart");

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        log::debug("PlayLayer_resetLevel levelId:{}", TimeCounter::levelId);
        bool startpos = PlayLayer::get()->m_isTestMode;
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool prevstartpos = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isStartpos");
        bool prevnormal = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isNormal");
        if (startpos) {
            if (!prevstartpos) {
                log::info("startpos begin");
                TimeCounter::setStartTime(CounterType::Startpos);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", true);
            }
        }
        else {
            if (prevstartpos) {
                log::info("startpos end");
                TimeCounter::updateTotalTime(CounterType::Startpos);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
            }
        }
        if (!startpos && !practice) {
            if (!prevnormal) {
                log::info("normal begin");
                TimeCounter::setStartTime(CounterType::Normal);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", true);
            }
        }
        else {
            if (prevnormal) {
                log::info("normal end");
                TimeCounter::updateTotalTime(CounterType::Normal);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
            }
        } else {
            log::debug("PlayLayer_resetLevel SKIP");
            std::string mode = "";
            log::debug("PlayLayer_resetLevel startpos:{}, practice:{}", startpos, practice);
            if (startpos) {mode = "startpos";} else if (!practice) {mode = "normal";}
            if (practice) {mode = "practice";} 
            Mod::get()->setSavedValue("FirstAtt", mode);
        }
    }
    

    void levelComplete() {
        PlayLayer::levelComplete();
        TimeCounter::updateTotalTime(CounterType::NoPause);
    }

    void togglePracticeMode(bool p0) {
        PlayLayer::togglePracticeMode(p0);
        if (p0) {
            TimeCounter::setStartTime(CounterType::Practice);
            if (!PlayLayer::get()->m_isTestMode) {
                TimeCounter::updateTotalTime(CounterType::Normal);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
                log::debug("PlayLayer_togglePracticeMode_normalstop_isNormalfalse");
            }
        }
        else {
            TimeCounter::updateTotalTime(CounterType::Practice);
        }
    }

    void fullReset() {
        PlayLayer::fullReset();
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onQuit() {
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;
        if (practice) {TimeCounter::updateTotalTime(CounterType::Practice);}
        if (startpos) {TimeCounter::updateTotalTime(CounterType::Startpos);}
        if (!practice && !startpos) {TimeCounter::updateTotalTime(CounterType::Normal);}
        PlayLayer::onQuit();
        TimeCounter::updateTotalTime(CounterType::Total);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
        std::string mode = "";
        Mod::get()->setSavedValue("FirstAtt", mode);
        log::debug("PlayLayer_onQuit_withpauseallstop_isStartposisNormalfalse_FirstAttnone");
        log::debug("PlayLayer_onQuit practice:{}, startpos:{}", practice, startpos);
        // log::info("{} attemptTime: {}", this->m_level->m_levelName, this->m_level->m_attemptTime.value());
        // log::info("{} workingTime: {}", this->m_level->m_levelName, this->m_level->m_workingTime);
        // log::info("{} workingTime2: {}", this->m_level->m_levelName, this->m_level->m_workingTime2);
        // logging
        auto id = TimeCounter::levelId;
        auto name = TimeCounter::levelName;
        auto time = TimeCounter::getTotalTime(CounterType::Total);
        auto timenormal = TimeCounter::getTotalTime(CounterType::Normal);
        auto timepractice = TimeCounter::getTotalTime(CounterType::Practice);
        auto timestartpos = TimeCounter::getTotalTime(CounterType::Startpos);
        auto timenopause = TimeCounter::getTotalTime(CounterType::NoPause);
        log::info("{}: {} with pauses", name, time);
        log::info("{}: {} normal", name, timenormal);
        log::info("{}: {} practice", name, timepractice);
        log::info("{}: {} startpos", name, timestartpos);
        log::info("{}: {} without pauses", name, timenopause);
    }

};