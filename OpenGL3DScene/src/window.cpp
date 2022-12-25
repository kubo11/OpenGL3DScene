#include "window.h"

Window::Window(const std::string& title, int width, int height)
    : title_(title), width_(width), height_(height) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (window_ == nullptr) {
    // TODO error
  }
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Window::LoadAsCurrent() {
  glfwMakeContextCurrent(window_);

  gladLoadGL();
  glViewport(0, 0, width_, height_);
}

void Window::SetLoopFunc(std::function<void(void)> loop_func) {
  loop_func_ = loop_func;
}

void Window::RunMainLoop() {
  while (!glfwWindowShouldClose(window_)) {
    loop_func_();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}