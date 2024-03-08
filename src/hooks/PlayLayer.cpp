#include <Geode/modify/PlayLayer.hpp>
#include "../TimeCounter.hpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel *level, bool p1, bool p2) {
        if (!PlayLayer::init(level, p1, p2)) {
            return false;
        }

        auto levelId = TimeCounter::getLevelId(level);
        TimeCounter::setStartTime(levelId);

        return true;
    }

    void onQuit() {
        PlayLayer::onQuit();

        auto levelId = TimeCounter::getLevelId(this->m_level);
        TimeCounter::updateTotalTime(levelId);
    }
};