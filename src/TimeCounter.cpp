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
    long long currentTime = getCurrentTimeSeconds();

    auto id = appendType(type, TimeCounter::sessionId);
    Mod::get()->setSavedValue(id, currentTime);
}

void TimeCounter::updateTotalTime(CounterType type) {
    if (Mod::get()->getSavedValue<std::string>("CurrentLevel") != "") {
        long long currentTime = getCurrentTimeSeconds();
        long long startTime = TimeCounter::getStartTime(type);
        long long delta = currentTime - startTime;

        long long oldTime = TimeCounter::getTotalTime(type);
        long long newTime = oldTime + delta;

        auto id = appendType(type, TimeCounter::levelId);
        Mod::get()->setSavedValue(id, newTime);
    }
}

long long TimeCounter::getStartTime(CounterType type) {
    auto id = appendType(type, TimeCounter::sessionId);
    return Mod::get()->getSavedValue<long long>(id);
}

long long TimeCounter::getTotalTime(CounterType type) {
    auto id = appendType(type, TimeCounter::levelId);
    return Mod::get()->getSavedValue<long long>(id);
}

void TimeCounter::recoverLostTime(CounterType type) {
    auto savedLevel = Mod::get()->getSavedValue<std::string>("CurrentLevel");
    auto savedLevelId = appendType(type, savedLevel);
    auto savedSession = savedLevel + "-session";
    auto savedSessionId = appendType(type, savedSession);

    long long savedTime = Mod::get()->getSavedValue<long long>("SavedTime");
    long long startTime = Mod::get()->getSavedValue<long long>(savedSessionId);
    long long delta = savedTime - startTime;

    long long oldTime = Mod::get()->getSavedValue<long long>(savedLevelId);
    long long newTime = oldTime + delta;

    Mod::get()->setSavedValue(savedLevelId, newTime);
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
    if (TimeCounter::getLastDay() != today) {
            Mod::get()->setSavedValue(TimeCounter::levelId + "DaysCounter", TimeCounter::getTotalDays() + 1);
            Mod::get()->setSavedValue(TimeCounter::levelId + "LastDay", today);
        }
}

int TimeCounter::getTotalDays() {
    int days = Mod::get()->getSavedValue<int>(TimeCounter::levelId + "DaysCounter");
    if (days > 0) {return days;} else {return 0;}
}

std::string TimeCounter::getLastDay() {
    return Mod::get()->getSavedValue<std::string>(TimeCounter::levelId + "LastDay");
}