#include <Geode/modify/MenuLayer.hpp>
#include "../TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

using namespace geode::prelude;

void recoverTime(std::string level) {
    TimeCounter::recoverLostTime(CounterType::Total);
    // log::debug("MenuLayer_init_totalrecovered");
    if (!Mod::get()->getSavedValue<bool>("SavedOnPause")) {
        TimeCounter::recoverLostTime(CounterType::NoPause);
        // log::debug("MenuLayer_init_nopauserecovered");
    }
    if (Mod::get()->getSavedValue<bool>("SavedStartpos")) {
        TimeCounter::recoverLostTime(CounterType::Startpos);
        // log::debug("MenuLayer_init_startposrecovered");
    }
    if (Mod::get()->getSavedValue<bool>("SavedPractice")) {
        TimeCounter::recoverLostTime(CounterType::Practice);
        // log::debug("MenuLayer_init_practicerecovered");
    } else if (!Mod::get()->getSavedValue<bool>("SavedStartpos")) {
        TimeCounter::recoverLostTime(CounterType::Normal);
        // log::debug("MenuLayer_init_normalrecovered");
    }
    std::string empty = "";
    Mod::get()->setSavedValue("SavedLevel", empty);
}

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto saved_level = Mod::get()->getSavedValue<std::string>("SavedLevel");
        // log::debug("MenuLayer_init SavedLevel: {}", saved_level);
        if (saved_level != "") {
            recoverTime(saved_level);
        }

        return true;
    }
};