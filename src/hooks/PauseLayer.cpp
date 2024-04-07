#include <Geode/modify/PauseLayer.hpp>
#include "../TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {  
        PauseLayer::customSetup();
        TimeCounter::updateTotalTimeNoPause();
    }

    void onResume(CCObject* sender) {
        PauseLayer::onResume(sender);
        TimeCounter::setStartTimeNoPause();
    }

    void onNormalMode(CCObject* sender) {
        PauseLayer::onNormalMode(sender);
        TimeCounter::setStartTimeNoPause();
    }

    void onPracticeMode(CCObject* sender) {
        PauseLayer::onPracticeMode(sender);
        TimeCounter::setStartTimeNoPause();
    }

    void onRestart(CCObject* sender) {
        PauseLayer::onRestart(sender);
        TimeCounter::setStartTimeNoPause();
    }

    void onRestartFull(CCObject* sender) {
        PauseLayer::onRestartFull(sender);
        TimeCounter::setStartTimeNoPause();
    }

    void onEdit(CCObject* sender) {
        bool practice = PlayLayer::get()->m_isPracticeMode;
        bool startpos = PlayLayer::get()->m_isTestMode;
        if (practice) {TimeCounter::updateTotalTimePractice();}
        if (startpos) {TimeCounter::updateTotalTimeStartpos();}
        if (!practice && !startpos) {TimeCounter::updateTotalTimeNormal();}
        PauseLayer::onEdit(sender);
        TimeCounter::updateTotalTime();
        log::info("Editor");
        Mod::get()->setSavedValue(TimeCounter::levelId + "isStartpos", false);
        Mod::get()->setSavedValue(TimeCounter::levelId + "isNormal", false);
    }
};