#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] = {
    -0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,   -0.5f * float(sqrt(3)) / 3,     0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f, 0.0f, 0.0f, 1.0f,
};

  GLFWwindow* window = glfwCreateWindow(800, 800, "DemoWindow", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create a GLFW window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  gladLoadGL();
  glViewport(0, 0, 800, 800);

  Shader defaultShader = Shader("default");

  //GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  //glCompileShader(vertexShader);

  //GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  //glCompileShader(fragmentShader);

  //GLuint shaderProgram = glCreateProgram();

  //glAttachShader(shaderProgram, vertexShader);
  //glAttachShader(shaderProgram, fragmentShader);
  //glLinkProgram(shaderProgram);

  //glDeleteShader(vertexShader);
  //glDeleteShader(fragmentShader);

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

  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    defaultShader.Activate();
    //glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteVertexArrays(1, &VBO);
  //glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
