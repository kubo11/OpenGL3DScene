#include "app.h"
#include "error_log.h"

App::App() {
  glfwInit();

  window_ = std::make_unique<Window>("DemoWindow", 800, 800);
  scene_ = std::make_unique<Scene>();
}

App::~App() {
  glfwTerminate();
}

void App::Run() {
  if (!window_->IsGood()) {
    ERROR << "Could not create OpenGL window" << std::endl;
    return;
  }
  window_->LoadAsCurrent();

  scene_->LoadData();

  window_->SetLoopFunc([&]() { scene_->Render(); });
  window_->RunMainLoop();
}
