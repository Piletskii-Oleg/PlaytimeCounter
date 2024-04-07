#ifndef PLAYTIMECOUNTER_TIMECOUNTER_HPP
#define PLAYTIMECOUNTER_TIMECOUNTER_HPP

using namespace geode::prelude;

enum class CounterType {
    Normal,
    Practice,
    Startpos,
    NoPause,
    Total
};

class TimeCounter {
private:
    static GJGameLevel* currentLevel;
    static std::string sessionId;
    static void setLevelId(GJGameLevel* level);
    static std::string appendType(CounterType type, const std::string& id);
public:
    TimeCounter() = delete;
    static std::string levelId;
    static std::string levelName;
    static void setLevel(GJGameLevel* level);
    static void setStartTime(CounterType type);
    static long long getStartTime(CounterType type);
    static void updateTotalTime(CounterType type);
    static long long getTotalTime(CounterType type);
};

#endif //PLAYTIMECOUNTER_TIMECOUNTER_HPP