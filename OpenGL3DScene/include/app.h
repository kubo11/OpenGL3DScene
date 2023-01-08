#ifndef OPENGL3DSCENE_APP_H_
#define OPENGL3DSCENE_APP_H_

#include "scene.h"
#include "user_input.h"
#include "window.h"

class App {
 public:
  App();
  App(App&) = delete;
  ~App();

  void Run();

 private:
  std::unique_ptr<KeyboardInput> keyboard_input_;
  std::unique_ptr<MouseInput> mouse_input_;
  std::unique_ptr<Scene> scene_;
  std::shared_ptr<Window> window_;

  void SetupInputs();
};

#endif	// OPENGL3DSCENE_APP_H_
