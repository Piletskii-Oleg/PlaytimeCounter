#include "TimeUtils.hpp"

long long getCurrentTimeSeconds() {
    using namespace std::chrono;

    auto now = system_clock::now();
    return time_point_cast<seconds>(now).time_since_epoch().count();
}