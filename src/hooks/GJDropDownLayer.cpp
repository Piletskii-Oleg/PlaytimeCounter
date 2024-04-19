#include <Geode/modify/GJDropDownLayer.hpp>
#include "../TimeCounter.hpp"

using namespace geode::prelude;

class $modify(GJDropDownLayer) {
    void exitLayer(CCObject* p0) {
        GJDropDownLayer::exitLayer(p0);
        TimeCounter::setStartTime(CounterType::NoPause);
        // log::debug("GJDropDownLayer_exitLayer_nopausestart");
    }
};