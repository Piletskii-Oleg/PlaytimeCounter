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

        PauseLayer::onEdit(sender);
        TimeCounter::updateTotalTime();
    }
};