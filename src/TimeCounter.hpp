#ifndef PLAYTIMECOUNTER_TIMECOUNTER_HPP
#define PLAYTIMECOUNTER_TIMECOUNTER_HPP

using namespace geode::prelude;

typedef std::map<std::string, long long> TimeMap;

class TimeCounter {
private:
    static TimeMap levels;
public:
    TimeCounter() = delete;
    static std::string getLevelId(GJGameLevel* level);
    static long long getStartTime(const std::string& levelId);
    static void setStartTime(const std::string& levelId);
    static long long getTotalTime(const std::string& levelId);
    static void updateTotalTime(const std::string& levelId);
};

#endif //PLAYTIMECOUNTER_TIMECOUNTER_HPP