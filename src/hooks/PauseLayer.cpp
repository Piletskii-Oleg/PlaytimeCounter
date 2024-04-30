#include <Geode/modify/PauseLayer.hpp>
#include "../TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {  
        PauseLayer::customSetup();
        TimeCounter::updateTotalTime(CounterType::NoPause);
        TimeCounter::updateDays();
        Mod::get()->setSavedValue("SavedTime", getCurrentTimeSeconds());
        Mod::get()->setSavedValue("SavedOnPause", true);
        Mod::get()->setSavedValue("SavedPractice", PlayLayer::get()->m_isPracticeMode);
        // log::debug("PauseLayer_customSetup_nopausestop_recoverysaved");
    }

    void onResume(CCObject* sender) {
        PauseLayer::onResume(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PauseLayer_onResume_nopausestart");
    }

    void onNormalMode(CCObject* sender) {
        PauseLayer::onNormalMode(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PauseLayer_onNormalMode_nopausestart");
    }

    void onPracticeMode(CCObject* sender) {
        PauseLayer::onPracticeMode(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PauseLayer_onPracticeMode_nopausestart");
    }

    void onRestart(CCObject* sender) {
        PauseLayer::onRestart(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PauseLayer_onRestart_nopausestart");
    }

    void onRestartFull(CCObject* sender) {
        PauseLayer::onRestartFull(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("PauseLayer_onRestartFull_nopausestart");
    }

    void onEdit(CCObject* sender) {
        PauseLayer::onEdit(sender);
        TimeCounter::updateTotalTime(CounterType::Total);
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;
        if (practice) {TimeCounter::updateTotalTime(CounterType::Practice);}
        if (startpos) {TimeCounter::updateTotalTime(CounterType::Startpos);}
        if (!practice && !startpos) {TimeCounter::updateTotalTime(CounterType::Normal);}
        TimeCounter::updateDays();
        std::string empty = "";
        Mod::get()->setSavedValue("CurrentLevel", empty);
        Mod::get()->setSavedValue("FirstAtt", empty);
        Mod::get()->setSavedValue("isTotal", false);
        Mod::get()->setSavedValue("isComplete", false);
        Mod::get()->setSavedValue("isStartpos", false);
        Mod::get()->setSavedValue("isNormal", false);
        // log::debug("PauseLayer_onEdit_withpauseallstop_isTotalisCompleteisStartposisNormalfalse_FirstAttnone");
        // log::debug("PauseLayer_onEdit practice: {}, startpos: {}", practice, startpos);
    }
};