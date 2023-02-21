#include "app.h"
#include "error_log.h"

#define FPPCAMERA "fppcamera"

App::App() {
  glfwInit();

  window_ = std::make_shared<Window>("DemoWindow", 1080, 1080);
  window_->LoadAsCurrent();
  scene_ = std::make_unique<Scene>();

  SetupInputs();
}

App::~App() {
  scene_.reset();
  window_.reset();
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
  keyboard_input_ = std::make_shared<KeyboardInput>();
  keyboard_input_->AddScope(FPPCAMERA);
  mouse_input_ = std::make_shared<MouseInput>();
  mouse_input_->AddScope(FPPCAMERA);

  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_W, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(camera->GetOrientation());
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_S, GLFW_PRESS, [&]() {
    auto camera = scene_->current_camera;
      camera->Move(-camera->GetOrientation());
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_A, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(-glm::normalize(glm::cross(camera->GetOrientation(), camera->GetUp())));
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_D, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(glm::normalize(glm::cross(camera->GetOrientation(), camera->GetUp())));
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_SPACE, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(camera->GetUp());
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_LEFT_CONTROL, GLFW_PRESS, [&]() {
      auto camera = scene_->current_camera;
      camera->Move(-camera->GetUp());
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_0, GLFW_PRESS, [&]() {
      scene_->SetCamera(0);
      keyboard_input_->ChangeScope(UserInput::DefaultScope);
      mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_1, GLFW_PRESS, [&]() {
      scene_->SetCamera(1);
      keyboard_input_->ChangeScope(FPPCAMERA);
      mouse_input_->ChangeScope(FPPCAMERA);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_2, GLFW_PRESS, [&]() {
      scene_->SetCamera(2);
      keyboard_input_->ChangeScope(UserInput::DefaultScope);
      mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_3, GLFW_PRESS, [&]() {
      scene_->SetCamera(3);
      keyboard_input_->ChangeScope(UserInput::DefaultScope);
      mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(FPPCAMERA, GLFW_KEY_0, GLFW_PRESS, [&]() {
    scene_->SetCamera(0);
    keyboard_input_->ChangeScope(UserInput::DefaultScope);
    mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(FPPCAMERA, GLFW_KEY_1, GLFW_PRESS, [&]() {
    scene_->SetCamera(1);
    keyboard_input_->ChangeScope(FPPCAMERA);
    mouse_input_->ChangeScope(FPPCAMERA);
    });
  keyboard_input_->AddBinding(FPPCAMERA, GLFW_KEY_2, GLFW_PRESS, [&]() {
    scene_->SetCamera(2);
    keyboard_input_->ChangeScope(UserInput::DefaultScope);
    mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(FPPCAMERA, GLFW_KEY_3, GLFW_PRESS, [&]() {
    scene_->SetCamera(3);
    keyboard_input_->ChangeScope(UserInput::DefaultScope);
    mouse_input_->ChangeScope(UserInput::DefaultScope);
    });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_ESCAPE, GLFW_PRESS, [&]() {
      exit(0);
    });
  static Timer fog_timer = Timer(0.5, [&]() { scene_->fog_level_ = (scene_->fog_level_ + 1) % Scene::max_fog_level; });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_F, GLFW_PRESS, [&]() {
      fog_timer.Tick();
    });
  static Timer wiggle_timer = Timer(0.5, [&]() { scene_->enable_wiggling = !scene_->enable_wiggling; });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_J, GLFW_PRESS, [&]() {
      wiggle_timer.Tick();
    });
  static Timer phong_timer = Timer(0.5, [&]() { scene_->SetShader(0); });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_H, GLFW_PRESS, [&]() {
      phong_timer.Tick();
    });
  static Timer gouraud_timer = Timer(0.5, [&]() { scene_->SetShader(1); });
  keyboard_input_->AddBinding(UserInput::DefaultScope, GLFW_KEY_G, GLFW_PRESS, [&]() {
      gouraud_timer.Tick();
    });

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
  mouse_input_->AddBinding(FPPCAMERA, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, [&]() {
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

    scene_->RotateModelLights(rotX, rotY);

    window_->SetCursorPos(centerX, centerY);
  });
  mouse_input_->AddBinding(FPPCAMERA, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, [&]() {
    window_->SetCursorMode(GLFW_CURSOR_NORMAL);
    mouse_input_->first_click = true;
  });
}

void App::SetGlobalScope(const std::string& scope) {
  keyboard_input_->ChangeScope(scope);
  mouse_input_->ChangeScope(scope);
}
