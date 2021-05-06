#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

// A simple clock (stopwatch) that uses std::chrono to measure time.
struct Clock
{
    Clock() {start();}

    // Restarts the clock and returns the current clock value.
    float restart()
    {
        float elapse = elapsed();
        start();
        return elapse;
    }

    // Returns the elapsed time in seconds.
    float elapsed()
    {
        std::chrono::milliseconds elapse = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);
        return elapse.count() / 1000.0f;
    }

    private:
    void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    std::chrono::high_resolution_clock::time_point start_time;
};

#endif