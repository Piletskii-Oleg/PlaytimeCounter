#include <Geode/modify/PlayLayer.hpp>
#include "../TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel *level, bool p1, bool p2) {
        if (!PlayLayer::init(level, p1, p2)) {
            return false;
        }

        TimeCounter::setLevel(level);
        TimeCounter::setStartTime(CounterType::Total);
        TimeCounter::setStartTime(CounterType::NoPause);
        TimeCounter::updateDays();
        // log::debug("PlayLayer_init_totalstart_nopausestart_updatedays");

        std::string mode = Mod::get()->getSavedValue<std::string>("FirstAtt");
        if (mode == "startpos") {
            TimeCounter::setStartTime(CounterType::Startpos);
            Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", true);
            Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
            // log::debug("PlayLayer_init_startposstart_isStartpostrue_isNormalfalse");
        }
        if (mode == "normal") {
            TimeCounter::setStartTime(CounterType::Normal);
            Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", true);
            Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
            // log::debug("PlayLayer_init_normalstart_isNormaltrue_isStartposfalse");
        }
        if (mode == "practice") {
            TimeCounter::setStartTime(CounterType::Practice);
        } 
        // log::debug("PlayLayer_init FirstAtt mode:{}", mode);

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        // log::debug("PlayLayer_resetLevel levelId:{}", TimeCounter::levelId);
        bool startpos = PlayLayer::get()->m_isTestMode;
        bool practice = PlayLayer::get()->m_isPracticeMode;
        // log::debug("PlayLayer_resetLevel startpos and practice get");
        if (TimeCounter::levelId != "") {
            bool prevstartpos = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isStartpos");
            bool prevnormal = Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isNormal");
            // log::debug("PlayLayer_resetLevel startpos:{}, practice:{}, prevstartpos:{}, prevnormal:{}, id:{}", startpos, practice, prevstartpos, prevnormal, TimeCounter::levelId);
            if (startpos) {
                if (!prevstartpos) {
                    TimeCounter::setStartTime(CounterType::Startpos);
                    Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", true);
                    // log::debug("PlayLayer_resetLevel_startposstart_isStartpostrue");
                }
            }
            else {
                if (prevstartpos) {
                    TimeCounter::updateTotalTime(CounterType::Startpos);
                    Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
                    // log::debug("PlayLayer_resetLevel_startposstop_isStartposfalse");
                }
            }
            if (!startpos && !practice) {
                if (!prevnormal) {
                    TimeCounter::setStartTime(CounterType::Normal);
                    Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", true);
                    // log::debug("PlayLayer_resetLevel_normalstart_isNormaltrue");
                }
            }
            else {
                if (prevnormal) {
                    TimeCounter::updateTotalTime(CounterType::Normal);
                    Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
                    // log::debug("PlayLayer_resetLevel_normalstop_isNormalfalse");
                }
            }
        } else {
            // log::debug("PlayLayer_resetLevel SKIP");
            std::string mode = "";
            // log::debug("PlayLayer_resetLevel startpos:{}, practice:{}", startpos, practice);
            if (startpos) {mode = "startpos";} else if (!practice) {mode = "normal";}
            if (practice) {mode = "practice";} 
            Mod::get()->setSavedValue("FirstAtt", mode);
        }
    }
    

    void levelComplete() {
        PlayLayer::levelComplete();
        TimeCounter::updateTotalTime(CounterType::NoPause);
        // log::debug("PlayLayer_levelComplete_nopausestop");
    }

    void togglePracticeMode(bool p0) {
        PlayLayer::togglePracticeMode(p0);
        if (p0) {
            TimeCounter::setStartTime(CounterType::Practice);
            // log::debug("PlayLayer_togglePracticeMode_practicestart");
            if (Mod::get()->getSavedValue<bool>(TimeCounter::levelId + "isNormal")) {
                TimeCounter::updateTotalTime(CounterType::Normal);
                Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
                // log::debug("PlayLayer_togglePracticeMode_normalstop_isNormalfalse");
            }
        }
        else {
            TimeCounter::updateTotalTime(CounterType::Practice);
            // log::debug("PlayLayer_togglePracticeMode_practicestop");
        }
    }

    void fullReset() {
        PlayLayer::fullReset();
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PlayLayer_fullReset_nopausestart");
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
        // log::debug("PlayLayer_onQuit_withpauseallstop_isStartposisNormalfalse_FirstAttnone");
        // log::debug("PlayLayer_onQuit practice:{}, startpos:{}", practice, startpos);
        // log::info("{} attemptTime: {}", this->m_level->m_levelName, this->m_level->m_attemptTime.value());
        // log::info("{} workingTime: {}", this->m_level->m_levelName, this->m_level->m_workingTime);
        // log::info("{} workingTime2: {}", this->m_level->m_levelName, this->m_level->m_workingTime2);
        // logging
        auto id = TimeCounter::levelId;
        auto name = TimeCounter::levelName;

        auto time = TimeCounter::getTotalTime(CounterType::Total);
        auto time_h = time / 3600;
        auto time_min = (time - time_h*3600) / 60;
        auto time_sec = time - time_h*3600 - time_min*60;

        auto timenormal = TimeCounter::getTotalTime(CounterType::Normal);
        auto timenormal_h = timenormal / 3600;
        auto timenormal_min = (timenormal - timenormal_h*3600) / 60;
        auto timenormal_sec = timenormal - timenormal_h*3600 - timenormal_min*60;

        auto timepractice = TimeCounter::getTotalTime(CounterType::Practice);
        auto timepractice_h = timepractice / 3600;
        auto timepractice_min = (timepractice - timepractice_h*3600) / 60;
        auto timepractice_sec = timepractice - timepractice_h*3600 - timepractice_min*60;

        auto timestartpos = TimeCounter::getTotalTime(CounterType::Startpos);
        auto timestartpos_h = timestartpos / 3600;
        auto timestartpos_min = (timestartpos - timestartpos_h*3600) / 60;
        auto timestartpos_sec = timestartpos - timestartpos_h*3600 - timestartpos_min*60;

        auto timenopause = TimeCounter::getTotalTime(CounterType::NoPause);
        auto timenopause_h = timenopause / 3600;
        auto timenopause_min = (timenopause - timenopause_h*3600) / 60;
        auto timenopause_sec = timenopause - timenopause_h*3600 - timenopause_min*60;

        auto days = TimeCounter::getTotalDays();
        auto lastday = TimeCounter::getLastDay();
        log::info("*LEVEL NAME: {}*", name);
        log::info(" {}:{}:{} - Total Playtime", time_h, time_min, time_sec);
        log::info(" {}:{}:{} - Normal Mode", timenormal_h, timenormal_min, timenormal_sec);
        log::info(" {}:{}:{} - Practice Mode", timepractice_h, timepractice_min, timepractice_sec);
        log::info(" {}:{}:{} - Start Position", timestartpos_h, timestartpos_min, timestartpos_sec);
        log::info(" {}:{}:{} - Without Pauses", timenopause_h, timenopause_min, timenopause_sec);
        log::info(" Days Entering Level - {}", days);
    }

};