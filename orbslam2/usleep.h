#pragma once
#include <thread>
#include <chrono>

inline void usleep(unsigned int us) {
  std::this_thread::sleep_for(std::chrono::microseconds(us));
}