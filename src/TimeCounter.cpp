#include "TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

TimeMap TimeCounter::levels {};

std::string TimeCounter::getLevelId(GJGameLevel *level) {
    if (level == nullptr) {
        return "";
    }

    auto levelId = std::to_string(level->m_levelID.value());

    if (level->m_dailyID > 0) {
        levelId += "-daily";
    }

    return levelId;
}

void TimeCounter::setStartTime(const std::string& levelId) {
    auto sessionId = levelId + "sessionId";
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(sessionId, currentTime);
}

void TimeCounter::updateTotalTime(const std::string& levelId) {
    auto sessionId = levelId + "session";

    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTime(levelId);
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTime(levelId);
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(levelId, newTime);
}

long long TimeCounter::getStartTime(const std::string &levelId) {
    auto sessionId = levelId + "session";
    return Mod::get()->getSavedValue<long long>(sessionId);
}

long long TimeCounter::getTotalTime(const std::string &levelId) {
    return Mod::get()->getSavedValue<long long>(levelId);
}
