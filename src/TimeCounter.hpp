#ifndef PLAYTIMECOUNTER_TIMECOUNTER_HPP
#define PLAYTIMECOUNTER_TIMECOUNTER_HPP

using namespace geode::prelude;

typedef std::map<std::string, long long> TimeMap;

class TimeCounter {
private:
    static GJGameLevel* currentLevel;
    static std::string levelId;
    static std::string sessionId;
    static void setLevelId(GJGameLevel* level);
public:
    TimeCounter() = delete;
    static std::string levelName;
    static void setLevel(GJGameLevel* level);
    static void setStartTime();
    static void setStartTimeNoPause();
    static long long getStartTime();
    static long long getStartTimeNoPause();
    static void updateTotalTime();
    static void updateTotalTimeNoPause();
    static long long getTotalTime();
    static long long getTotalTimeNoPause();
};

#endif //PLAYTIMECOUNTER_TIMECOUNTER_HPP