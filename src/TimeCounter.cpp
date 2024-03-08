#include "TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

GJGameLevel* TimeCounter::currentLevel = nullptr;
std::string TimeCounter::levelId;
std::string TimeCounter::sessionId;

void TimeCounter::setLevelId(GJGameLevel *level) {
    TimeCounter::levelId = std::to_string(level->m_levelID.value());

    if (level->m_dailyID > 0) {
        TimeCounter::levelId = TimeCounter::levelId + "-daily";
    }
}

void TimeCounter::setStartTime() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId, currentTime);
}

void TimeCounter::updateTotalTime() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTime();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTime();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId, newTime);
}

long long TimeCounter::getStartTime() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId);
}

long long TimeCounter::getTotalTime() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId);
}

void TimeCounter::setLevel(GJGameLevel *level) {
    TimeCounter::currentLevel = level;
    TimeCounter::setLevelId(level);
    TimeCounter::sessionId = TimeCounter::levelId + "-session";

    setStartTime();
}
