#include <Geode/modify/PauseLayer.hpp>
#include "TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {  
        PauseLayer::customSetup();
        TimeCounter::updateTotalTime(CounterType::NoPause);
    }

    void onResume(CCObject* sender) {
        PauseLayer::onResume(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onNormalMode(CCObject* sender) {
        PauseLayer::onNormalMode(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onPracticeMode(CCObject* sender) {
        PauseLayer::onPracticeMode(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onRestart(CCObject* sender) {
        PauseLayer::onRestart(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onRestartFull(CCObject* sender) {
        PauseLayer::onRestartFull(sender);
        TimeCounter::setStartTime(CounterType::NoPause);
    }

    void onEdit(CCObject* sender) {
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;

        if (practice) {TimeCounter::updateTotalTime(CounterType::Practice);}
        if (startpos) {TimeCounter::updateTotalTime(CounterType::Startpos);}
        if (!practice && !startpos) {TimeCounter::updateTotalTime(CounterType::Normal);}

        PauseLayer::onEdit(sender);
        TimeCounter::updateTotalTime(CounterType::Total);

        log::info("Editor");

        Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
        std::string mode = "";
        Mod::get()->setSavedValue("FirstAtt", mode);
        log::debug("PauseLayer_onEdit_withpauseallstop_isStartposisNormalfalse_FirstAttnone");
        log::debug("PauseLayer_onEdit practice: {}, startpos: {}", practice, startpos);
    }
};