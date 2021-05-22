#include "clock.hpp"

float Clock::restart() {
    float elapse = elapsed();
    start();
    return elapse;
}

float Clock::elapsed() {
    std::chrono::milliseconds elapse = 
    std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::high_resolution_clock::now() - start_time);
    
    return elapse.count() / 1000.0f;
}