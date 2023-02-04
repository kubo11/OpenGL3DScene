#include "window.h"

#include "error_log.h"

Window::Window(const std::string& title, int width, int height)
    : title_(title), width_(width), height_(height) {

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
}

Window::~Window() {
  // all windows ar edestroyed by call to glfwTerminate
}

void Window::LoadAsCurrent() {
  glfwMakeContextCurrent(window_);

  GL_CHECK(gladLoadGL());
  GL_CHECK(glViewport(0, 0, width_, height_));
}

void Window::SetLoopFunc(std::function<void(void)> loop_func) {
  loop_func_ = loop_func;
}

void Window::RunMainLoop() {
  while (!glfwWindowShouldClose(window_)) {
    loop_func_();
    GL_CHECK(glfwSwapBuffers(window_));
    GL_CHECK(glfwPollEvents());
  }
}

bool Window::IsGood() {
  return window_ != nullptr;
}

const int Window::GetWidth() const {
  return width_;
}

const int Window::GetHeight() const {
  return height_;
}

void Window::SetCursorMode(GLenum mode) {
  GL_CHECK(glfwSetInputMode(window_, GLFW_CURSOR, mode));
}

void Window::GetCursorPos(double* posX, double* posY) {
  GL_CHECK(glfwGetCursorPos(window_, posX, posY));
}

void Window::SetCursorPos(double posX, double posY) {
  GL_CHECK(glfwSetCursorPos(window_, posX, posY));
}

GLenum Window::GetKey(GLenum key) {
  return glfwGetKey(window_, key);
}

GLenum Window::GetMouseButton(GLenum mouse_button) {
  return glfwGetMouseButton(window_, mouse_button);
}
