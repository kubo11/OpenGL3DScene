#ifndef OPENGL3DSCENE_APP_H_
#define OPENGL3DSCENE_APP_H_

#include "window.h"
#include "scene.h"

class App {
 public:
  App();
  App(App&) = delete;
  ~App();

  void Run();

 private:
  std::unique_ptr<Window> window_;
  std::unique_ptr<Scene> scene_;
};

#endif	// OPENGL3DSCENE_APP_H_
