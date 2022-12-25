#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "window.h"

int main() {
  Window window = Window("DemoWindow", 800, 800);
  window.LoadAsCurrent();

  GLfloat vertices[] = {
    -0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,   -0.5f * float(sqrt(3)) / 3,     0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f, 0.0f, 0.0f, 1.0f,
};

  Shader defaultShader = Shader("default");

  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  window.SetLoopFunc([&]() {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    defaultShader.Activate();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  });

  window.RunMainLoop();

  glDeleteVertexArrays(1, &VAO);
  glDeleteVertexArrays(1, &VBO);
  glfwTerminate();
  return 0;
}
