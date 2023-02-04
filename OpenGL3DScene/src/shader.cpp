#include "shader.h"

#include <filesystem>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
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
  GL_CHECK(glShaderSource(vertexShader, 1, &vertexShaderSourceC, nullptr));
  glCompileShader(vertexShader);
  CheckShaderCompileErrors(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_CHECK(glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, nullptr));
  glCompileShader(fragmentShader);
  CheckShaderCompileErrors(fragmentShader);

  ID_ = glCreateProgram();

  GL_CHECK(glAttachShader(ID_, vertexShader));
  GL_CHECK(glAttachShader(ID_, fragmentShader));

  GL_CHECK(glLinkProgram(ID_));
  GL_CHECK(CheckProgramCompileErrors(ID_));

  GL_CHECK(glDeleteShader(vertexShader));
  GL_CHECK(glDeleteShader(fragmentShader));
}

Shader::~Shader() {
  GL_CHECK(glDeleteProgram(ID_));
}

void Shader::Activate() {
  GL_CHECK(glUseProgram(ID_));
}

const GLuint& Shader::GetID() const {
  return ID_;
}

void Shader::SetInt(const std::string& name, int value) {
  int id = glGetUniformLocation(ID_, name.c_str());
  GL_CHECK(glUniform1i(id, value));
}

void Shader::SetFloat(const std::string& name, float value) {
  int id = glGetUniformLocation(ID_, name.c_str());
  GL_CHECK(glUniform1f(id, value));
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) {
  int id = glGetUniformLocation(ID_, name.c_str());
  GL_CHECK(glUniform3f(id, value.x, value.y, value.z));
}

void Shader::SetMat4(const std::string& name, int count, bool transpose, glm::mat4 value) {
  int id = glGetUniformLocation(ID_, name.c_str());
  GL_CHECK(glUniformMatrix4fv(id, count, transpose, glm::value_ptr(value)));
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