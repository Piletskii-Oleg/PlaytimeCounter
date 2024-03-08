#include "TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

GJGameLevel* currentLevel = nullptr;

void TimeCounter::setLevelId(GJGameLevel *level) {
    levelId = std::to_string(level->m_levelID.value());

    if (level->m_dailyID > 0) {
        levelId += "-daily";
    }
}

void TimeCounter::setStartTime() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(sessionId, currentTime);
}

void TimeCounter::updateTotalTime() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTime();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTime();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(levelId, newTime);
}

long long TimeCounter::getStartTime() {
    return Mod::get()->getSavedValue<long long>(sessionId);
}

long long TimeCounter::getTotalTime() {
    return Mod::get()->getSavedValue<long long>(levelId);
}

void TimeCounter::setLevel(GJGameLevel *level) {
    currentLevel = level;
    TimeCounter::setLevelId(level);
    sessionId = levelId + "session";

    setStartTime();
}
