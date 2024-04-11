#include "TimeUtils.hpp"

using namespace std::chrono;

long long getCurrentTimeSeconds() {
    auto now = system_clock::now();
    return time_point_cast<seconds>(now).time_since_epoch().count();
}

std::string getCurrentDate() {
    auto const time = current_zone()
        ->to_local(system_clock::now());
    return std::format("{:%Y-%m-%d}", time);
}