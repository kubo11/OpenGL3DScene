#ifndef OPENGL3DSCENE_APP_H_
#define OPENGL3DSCENE_APP_H_

#include "scene.h"
#include "user_input.h"
#include "window.h"

class App {
 public:
  App();
  ~App();

  App(const App&) = delete;
  App& operator = (const App&) = delete;

  App(App&&) noexcept = default;
  App& operator = (App&&) noexcept = default;

  void Run();
  void SetGlobalScope(const std::string&);

 private:
  std::shared_ptr<KeyboardInput> keyboard_input_;
  std::shared_ptr<MouseInput> mouse_input_;
  std::unique_ptr<Scene> scene_;
  std::shared_ptr<Window> window_;

  void SetupInputs();
};

#endif	// OPENGL3DSCENE_APP_H_
