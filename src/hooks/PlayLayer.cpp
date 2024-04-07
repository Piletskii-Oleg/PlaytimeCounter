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

        return true;
    }

    void levelComplete() {

        PlayLayer::levelComplete();
        TimeCounter::updateTotalTimeNoPause();
        TimeCounter::setStartTimeNoPause();
    }

    void fullReset() {

        PlayLayer::fullReset();
        TimeCounter::setStartTimeNoPause();
    }

    void onQuit() {
        
        PlayLayer::onQuit();
        TimeCounter::updateTotalTime();

        // log::info("{} attemptTime: {}", this->m_level->m_levelName, this->m_level->m_attemptTime.value());
        // log::info("{} workingTime: {}", this->m_level->m_levelName, this->m_level->m_workingTime);
        // log::info("{} workingTime2: {}", this->m_level->m_levelName, this->m_level->m_workingTime2);
        // logging
        auto name = TimeCounter::levelName;
        auto time = TimeCounter::getTotalTime();
        auto timenopause = TimeCounter::getTotalTimeNoPause();
        log::info("{}: {} with pauses", name, time);
        log::info("{}: {} without pauses", name, timenopause);
    } 
};