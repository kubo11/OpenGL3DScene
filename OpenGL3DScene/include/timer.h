#ifndef OPENGL3DSCENE_TIMER_H_
#define OPENGL3DSCENE_TIMER_H_

#include <functional>

class Timer {
 public:
  Timer(double, std::function<void(void)>);
  Timer(Timer&) = delete;
  ~Timer() = default;

  void Tick();
private:
  double previousTime_;
  double tickPeriod_;;
  std::function<void(void)> tickFunc_;
};

#endif  // OPENGL3DSCENE_TIMER_H_