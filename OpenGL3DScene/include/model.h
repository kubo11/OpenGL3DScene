#ifndef OPENGL3DSCENE_MODEL_H_
#define OPENGL3DSCENE_MODEL_H_

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "ebo.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

class Model {
 public:
  Model() = default;
  Model(std::vector<GLfloat>, std::vector<GLuint>, const std::optional<std::string>& = std::nullopt);
  ~Model() = default;

  Model(const Model&) = delete;
  Model& operator = (const Model&) = delete;

  Model(Model&&) noexcept = default;
  Model& operator = (Model&&) noexcept = default;

  void Render(Shader&);
  void Translate(glm::vec3);
  void Scale(glm::vec3);
  void Rotate(GLfloat, glm::vec3);

 protected:
  std::unique_ptr<EBO> ebo_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::unique_ptr<Texture> texture_ = nullptr;
  glm::mat4 model_matrix_ = glm::mat4(1.0f);
  int num_of_inidces_;
};

class SimpleLightModel : public Model {
 public:
  SimpleLightModel(std::vector<GLfloat>, std::vector<GLuint>);
  ~SimpleLightModel() = default;

  SimpleLightModel(const SimpleLightModel&) = delete;
  SimpleLightModel& operator = (const SimpleLightModel&) = delete;

  SimpleLightModel(SimpleLightModel&&) noexcept = default;
  SimpleLightModel& operator = (SimpleLightModel&&) noexcept = default;

  void Render(Shader&);
};

#endif  // OPENGL3DSCENE_MODEL_H_