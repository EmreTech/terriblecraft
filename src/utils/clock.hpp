#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

// A simple clock (stopwatch) that uses std::chrono to measure time.
struct Clock {
  Clock() { start(); }

  // Restarts the clock and returns the current clock value.
  float restart();

  // Returns the elapsed time in seconds.
  float elapsed();

private:
  void start() { start_time = std::chrono::high_resolution_clock::now(); }

  std::chrono::high_resolution_clock::time_point start_time;
};

#endif