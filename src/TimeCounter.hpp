#ifndef PLAYTIMECOUNTER_TIMECOUNTER_HPP
#define PLAYTIMECOUNTER_TIMECOUNTER_HPP

using namespace geode::prelude;

typedef std::map<std::string, long long> TimeMap;

class TimeCounter {
private:
    static GJGameLevel* currentLevel;
    static std::string levelId;
    static std::string sessionId;
    static long long getStartTime();
    static long long getTotalTime();
    static void setLevelId(GJGameLevel* level);
    static void setStartTime();
public:
    TimeCounter() = delete;
    static void setLevel(GJGameLevel* level);
    static void updateTotalTime();
};

#endif //PLAYTIMECOUNTER_TIMECOUNTER_HPP