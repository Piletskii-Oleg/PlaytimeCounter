#include <Geode/modify/PauseLayer.hpp>
#include "../TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {  
        PauseLayer::customSetup();
        TimeCounter::updateTotalTime(CounterType::NoPause);

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
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;
        if (practice) {TimeCounter::updateTotalTime(CounterType::Practice);}
        if (startpos) {TimeCounter::updateTotalTime(CounterType::Startpos);}
        if (!practice && !startpos) {TimeCounter::updateTotalTime(CounterType::Normal);}
        TimeCounter::updateTotalTime(CounterType::Total);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
        std::string empty = "";
        Mod::get()->setSavedValue("FirstAtt", empty);
        Mod::get()->setSavedValue("SavedLevel", empty);
        // log::debug("PauseLayer_onEdit_withpauseallstop_isStartposisNormalfalse_FirstAttnone");
        // log::debug("PauseLayer_onEdit practice: {}, startpos: {}", practice, startpos);

        TimeCounter::levelId = "";
    }
};