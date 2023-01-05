#include "timer.h"

#include <GLFW/glfw3.h>

Timer::Timer(double tickPeriod, std::function<void(void)> tickFunc) {
  tickPeriod_ = tickPeriod;
  previousTime_ = glfwGetTime();
  tickFunc_ = tickFunc;
}

void Timer::Tick() {
  double currentTime = glfwGetTime();
  if (currentTime - previousTime_ >= tickPeriod_) {
    tickFunc_();
    previousTime_ = currentTime;
  }
}