#ifndef OPENGL3DSCENE_SIMPLE_MODEL_H_
#define OPENGL3DSCENE_SIMPLE_MODEL_H_

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "ebo.h"
#include "error_log.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

namespace fs = std::filesystem;


class SimpleModel {
public:
  SimpleModel() = default;
  SimpleModel(std::vector<GLfloat>, std::vector<GLuint>);
  ~SimpleModel() = default;

  SimpleModel(const SimpleModel&) = delete;
  SimpleModel& operator = (const SimpleModel&) = delete;

  SimpleModel(SimpleModel&&) noexcept = default;
  SimpleModel& operator = (SimpleModel&&) noexcept = default;

  void Draw(Shader&);
  void Translate(glm::vec3);
  void Scale(glm::vec3);
  void Rotate(GLfloat, glm::vec3);

protected:
  std::unique_ptr<EBO> ebo_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  glm::mat4 model_matrix_ = glm::mat4(1.0f);
  unsigned int num_of_inidces_ = 0;
};

#endif // OPENGL3DSCENE_SIMPLE_MODEL_H_
