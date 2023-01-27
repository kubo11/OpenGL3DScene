#include "app.h"
#include "error_log.h"

App::App() {
  glfwInit();

  window_ = std::make_shared<Window>("DemoWindow", 800, 800);
  window_->LoadAsCurrent();
  scene_ = std::make_unique<Scene>();

  SetupInputs();
}

App::~App() {
  glfwTerminate();
}

void App::Run() {
  if (!window_->IsGood()) {
    ERROR << "Could not create OpenGL window" << std::endl;
    return;
  }

  window_->SetLoopFunc([&]() { 
    keyboard_input_->CaptureUserInput(window_);
    mouse_input_->CaptureUserInput(window_);
    scene_->Render(); 
   });
  window_->RunMainLoop();
}

void App::SetupInputs() {
  keyboard_input_ = std::make_unique<KeyboardInput>();
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_W, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(camera->Orientation);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_S, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(-camera->Orientation);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_A, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(-glm::normalize(glm::cross(camera->Orientation, camera->Up)));
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_D, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(glm::normalize(glm::cross(camera->Orientation, camera->Up)));
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_SPACE, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(camera->Up);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_LEFT_CONTROL, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(-camera->Up);
    });

  mouse_input_ = std::make_unique<MouseInput>();
  mouse_input_->AddBinding(UserInput::DefaultScope, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      float centerX = ((float)window_->GetWidth() / 2), centerY = ((float)window_->GetHeight() / 2);

      window_->SetCursorMode(GLFW_CURSOR_HIDDEN);

      if (mouse_input_->first_click)
      {
        window_->SetCursorPos(centerX, centerY);
        mouse_input_->first_click = false;
      }

      double mouseX;
      double mouseY;
      window_->GetCursorPos(&mouseX, &mouseY);

      float rotX = mouse_input_->sensitivity * (float)(mouseY - centerY) / window_->GetHeight();
      float rotY = mouse_input_->sensitivity * (float)(mouseX - centerX) / window_->GetWidth();

      camera->Rotate(rotX, rotY);

      window_->SetCursorPos(centerX, centerY);
    });
  mouse_input_->AddBinding(UserInput::DefaultScope, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, [&]() {
      window_->SetCursorMode(GLFW_CURSOR_NORMAL);
      mouse_input_->first_click = true;
    });
}