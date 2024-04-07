#ifndef PLAYTIMECOUNTER_TIMECOUNTER_HPP
#define PLAYTIMECOUNTER_TIMECOUNTER_HPP

using namespace geode::prelude;

typedef std::map<std::string, long long> TimeMap;

class TimeCounter {
private:
    static GJGameLevel* currentLevel;
    static std::string sessionId;
    static void setLevelId(GJGameLevel* level);
public:
    TimeCounter() = delete;
    static std::string levelId;
    static std::string levelName;
    static void setLevel(GJGameLevel* level);
    static void setStartTime();
    static void setStartTimeNormal();
    static void setStartTimePractice();
    static void setStartTimeStartpos();
    static void setStartTimeNoPause();
    static long long getStartTime();
    static long long getStartTimeNormal();
    static long long getStartTimePractice();
    static long long getStartTimeStartpos();
    static long long getStartTimeNoPause();
    static void updateTotalTime();
    static void updateTotalTimeNormal();
    static void updateTotalTimePractice();
    static void updateTotalTimeStartpos();
    static void updateTotalTimeNoPause();
    static long long getTotalTime();
    static long long getTotalTimeNormal();
    static long long getTotalTimePractice();
    static long long getTotalTimeStartpos();
    static long long getTotalTimeNoPause();
};

#endif //PLAYTIMECOUNTER_TIMECOUNTER_HPP