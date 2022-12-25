#include "shader.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "error_log.h"

namespace fs = std::filesystem;

Shader::Shader(const std::string& shaderName) {
  fs::path shadersDirectory = fs::current_path().parent_path() / "Shaders";
  std::string vertexShaderPath = (shadersDirectory / (shaderName + ".vert")).string();
  std::string fragmentShaderPath = (shadersDirectory / (shaderName + ".frag")).string();

  std::string vertexShaderSource = std::move(LoadShaderFile(vertexShaderPath));
  std::string fragmentShaderSource = std::move(LoadShaderFile(fragmentShaderPath));

  const GLchar* vertexShaderSourceC = vertexShaderSource.c_str();
  const GLchar* fragmentShaderSourceC = fragmentShaderSource.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSourceC, nullptr);
  glCompileShader(vertexShader);
  CheckShaderCompileErrors(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, nullptr);
  glCompileShader(fragmentShader);
  CheckShaderCompileErrors(fragmentShader);

  ID_ = glCreateProgram();

  glAttachShader(ID_, vertexShader);
  glAttachShader(ID_, fragmentShader);

  glLinkProgram(ID_);
  CheckProgramCompileErrors(ID_);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  glDeleteProgram(ID_);
}

void Shader::Activate() {
  glUseProgram(ID_);
}

const GLuint& Shader::GetID() {
  return ID_;
}

// private

std::string Shader::LoadShaderFile(const std::string& filename) {
  if (!fs::exists(filename)) {
    ERROR << "Could not locate file " << filename << std::endl;
    return "";
  }

  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();

  return std::move(content);
}

void Shader::CheckShaderCompileErrors(GLuint shader) {
  GLint hasCompiled;
  char infoBuffer[1024];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
  if (hasCompiled == GL_FALSE)
  {
    glGetShaderInfoLog(shader, 1024, NULL, infoBuffer);
    ERROR << "Shader compilation has failed" << std::endl << infoBuffer << std::endl;
  }
}

void Shader::CheckProgramCompileErrors(GLuint program) {
  GLint hasCompiled;
  char infoBuffer[1024];

  glGetProgramiv(program, GL_LINK_STATUS, &hasCompiled);
  if (hasCompiled == GL_FALSE)
  {
    glGetProgramInfoLog(program, 1024, NULL, infoBuffer);
    ERROR << "Shader program compilation has failed" << std::endl << infoBuffer << std::endl;
  }
}