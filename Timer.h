#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using clock_type = std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<clock_type>;

// Function to calculate duration in milliseconds
inline long long ms(time_point a, time_point b) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count();
}

#endif