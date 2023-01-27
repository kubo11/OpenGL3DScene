#ifndef OPENGL3DSCENE_TIMER_H_
#define OPENGL3DSCENE_TIMER_H_

#include <functional>

class Timer {
 public:
  Timer(double, std::function<void(void)>);
  ~Timer() = default;

  Timer(const Timer&) = delete;
  Timer& operator = (const Timer&) = delete;

  Timer(Timer&&) noexcept = default;
  Timer& operator = (Timer&&) noexcept = default;

  void Tick();
private:
  double previousTime_;
  double tickPeriod_;;
  std::function<void(void)> tickFunc_;
};

#endif  // OPENGL3DSCENE_TIMER_H_