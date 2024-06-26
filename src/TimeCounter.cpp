#include "TimeCounter.hpp"
#include "utils/TimeUtils.hpp"

GJGameLevel* TimeCounter::currentLevel = nullptr;
std::string TimeCounter::levelId;
std::string TimeCounter::levelName;
std::string TimeCounter::sessionId;

void TimeCounter::setLevelId(GJGameLevel *level) {
    if (level->m_levelID.value() > 0) {
        TimeCounter::levelId = std::to_string(level->m_levelID.value());
    } else if (level->m_originalLevel.value() > 0) {
        TimeCounter::levelId = std::to_string(level->m_originalLevel.value()) + "-copy";
    } else {
        TimeCounter::levelId = std::string(level->m_levelName) + "-mylevel";
    }

    TimeCounter::levelName = level->m_levelName;
    if (level->m_dailyID > 0) {
        TimeCounter::levelId = TimeCounter::levelId + "-daily";
    }

}

void TimeCounter::setStartTime(CounterType type) {
    auto currentTime = getCurrentTimeSeconds();

    auto id = appendType(type, TimeCounter::sessionId);
    Mod::get()->setSavedValue(id, currentTime);
}

void TimeCounter::updateTotalTime(CounterType type) {
    auto currentTime = getCurrentTimeSeconds();
    auto startTime = TimeCounter::getStartTime(type);
    auto delta = currentTime - startTime;

    auto oldTime = TimeCounter::getTotalTime(type);
    auto newTime = oldTime + delta;

    auto id = appendType(type, TimeCounter::levelId);
    Mod::get()->setSavedValue(id, newTime);
}

long long TimeCounter::getStartTime(CounterType type) {
    auto id = appendType(type, TimeCounter::sessionId);
    return Mod::get()->getSavedValue<long long>(id);
}

long long TimeCounter::getTotalTime(CounterType type) {
    auto id = appendType(type, TimeCounter::levelId);
    return Mod::get()->getSavedValue<long long>(id);
}

void TimeCounter::setLevel(GJGameLevel *level) {
    TimeCounter::currentLevel = level;
    TimeCounter::setLevelId(level);
    TimeCounter::sessionId = TimeCounter::levelId + "-session";
}

std::string TimeCounter::appendType(CounterType type, const std::string& id) {
    switch (type) {
        case CounterType::Normal:
            return id + "Normal";
        case CounterType::Practice:
            return id + "Practice";
        case CounterType::Startpos:
            return id + "Startpos";
        case CounterType::NoPause:
            return id + "NoPause";
        case CounterType::Total:
            return id;
    }

    return id;
}


void TimeCounter::updateDays() {
    auto today = getCurrentDate();
    int days = Mod::get()->getSavedValue<int>(TimeCounter::levelId + "DaysCounter");
    if (days > 0) {
        if (Mod::get()->getSavedValue<std::string>(TimeCounter::levelId + "LastDay") != today) {
            Mod::get()->setSavedValue(TimeCounter::levelId + "DaysCounter", days + 1);
            Mod::get()->setSavedValue(TimeCounter::levelId + "LastDay", today);
        }
    } else {
        Mod::get()->setSavedValue(TimeCounter::levelId + "DaysCounter", 1);
        Mod::get()->setSavedValue(TimeCounter::levelId + "LastDay", today);
    }
}

int TimeCounter::getTotalDays() {
    return Mod::get()->getSavedValue<int>(TimeCounter::levelId + "DaysCounter");
}

std::string TimeCounter::getLastDay() {
    return Mod::get()->getSavedValue<std::string>(TimeCounter::levelId + "LastDay");
}