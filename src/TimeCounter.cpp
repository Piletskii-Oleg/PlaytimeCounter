#include "TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

GJGameLevel* TimeCounter::currentLevel = nullptr;
std::string TimeCounter::levelId;
std::string TimeCounter::levelName;
std::string TimeCounter::sessionId;

void TimeCounter::setLevelId(GJGameLevel *level) {
    TimeCounter::levelId = std::to_string(level->m_levelID.value());
    TimeCounter::levelName = level->m_levelName;
    if (level->m_dailyID > 0) {
        TimeCounter::levelId = TimeCounter::levelId + "-daily";
    }
}



void TimeCounter::setStartTime() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId, currentTime);
}

void TimeCounter::setStartTimeNormal() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId + "Normal", currentTime);
}

void TimeCounter::setStartTimePractice() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId + "Practice", currentTime);
}

void TimeCounter::setStartTimeStartpos() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId + "Startpos", currentTime);
}

void TimeCounter::setStartTimeNoPause() {
    auto currentTime = getCurrentTimeSeconds();
    Mod::get()->setSavedValue(TimeCounter::sessionId + "NoPause", currentTime);
}



void TimeCounter::updateTotalTime() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTime();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTime();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId, newTime);
}

void TimeCounter::updateTotalTimeNormal() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTimeNormal();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTimeNormal();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId + "Normal", newTime);
}

void TimeCounter::updateTotalTimePractice() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTimePractice();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTimePractice();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId + "Practice", newTime);
}

void TimeCounter::updateTotalTimeStartpos() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTimeStartpos();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTimeStartpos();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId + "Startpos", newTime);
}

void TimeCounter::updateTotalTimeNoPause() {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTimeNoPause();
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTimeNoPause();
    auto newTime = oldTime + delta;
    Mod::get()->setSavedValue(TimeCounter::levelId + "NoPause", newTime);
}



long long TimeCounter::getStartTime() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId);
}

long long TimeCounter::getStartTimeNormal() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId + "Normal");
}

long long TimeCounter::getStartTimePractice() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId + "Practice");
}

long long TimeCounter::getStartTimeStartpos() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId + "Startpos");
}

long long TimeCounter::getStartTimeNoPause() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::sessionId + "NoPause");
}



long long TimeCounter::getTotalTime() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId);
}

long long TimeCounter::getTotalTimeNormal() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId + "Normal");
}

long long TimeCounter::getTotalTimePractice() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId + "Practice");
}

long long TimeCounter::getTotalTimeStartpos() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId + "Startpos");
}

long long TimeCounter::getTotalTimeNoPause() {
    return Mod::get()->getSavedValue<long long>(TimeCounter::levelId + "NoPause");
}



void TimeCounter::setLevel(GJGameLevel *level) {
    TimeCounter::currentLevel = level;
    TimeCounter::setLevelId(level);
    TimeCounter::sessionId = TimeCounter::levelId + "-session";
}
