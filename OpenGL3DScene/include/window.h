#ifndef OPENGL3DSCENE_WINDOW_H_
#define OPENGL3DSCENE_WINDOW_H_

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
 public:
   Window(const std::string&, int, int);
   Window(Window&) = delete;
   ~Window();
   void LoadAsCurrent();
   void SetLoopFunc(std::function<void(void)>);
   void RunMainLoop();

 private:
   GLFWwindow* window_;
   std::string title_;
   int width_;
   int height_;
   std::function<void(void)> loop_func_;
};

#endif  // OPENGL3DSCENE_WINDOW_H_
