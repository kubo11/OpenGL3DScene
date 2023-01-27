#include "model.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>

#include "error_log.h"

Model::Model(std::vector<GLfloat> vertices, std::vector<GLuint> indices, const std::optional<std::string>& texture_path) {
  num_of_inidces_ = indices.size();
  vao_ = std::make_unique<VAO>();
  vao_->Bind();
  vbo_ = std::make_unique<VBO>(1);
  vbo_->BufferData(0, vertices.data(), vertices.size() * sizeof(GLfloat));
  ebo_ = std::make_unique<EBO>(1);
  ebo_->BufferData(0, indices.data(), indices.size() * sizeof(GLuint));
  vao_->LinkAttrib(*vbo_.get(), 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_.get(), 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  vao_->LinkAttrib(*vbo_.get(), 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  if (texture_path.has_value() && std::filesystem::exists(texture_path.value())) {
    texture_ = std::make_unique<Texture>(texture_path.value().c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  }

  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();
}

void Model::Render(Shader& shader) {
  shader.SetMat4("model", 1, false, model_matrix_);

  shader.SetInt("material.diffuse", 0);
  shader.SetVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
  shader.SetFloat("material.shininess", 64.0f);

  if (texture_) texture_->Bind();
  vao_->Bind();
  glDrawElements(GL_TRIANGLES, num_of_inidces_, GL_UNSIGNED_INT, 0);
  vao_->Unbind();
  if (texture_) texture_->Unbind();
}

void Model::Translate(glm::vec3 position) {
  model_matrix_ = glm::translate(model_matrix_, position);
}

void Model::Scale(glm::vec3 scale) {
  model_matrix_ = glm::scale(model_matrix_, scale);
}

void Model::Rotate(GLfloat angle, glm::vec3 axis) {
  model_matrix_ = glm::rotate(model_matrix_, angle, axis);
}


SimpleLightModel::SimpleLightModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
  num_of_inidces_ = indices.size();
  vao_ = std::make_unique<VAO>();
  vao_->Bind();
  vbo_ = std::make_unique<VBO>(1);
  vbo_->BufferData(0, vertices.data(), vertices.size() * sizeof(GLfloat));
  ebo_ = std::make_unique<EBO>(1);
  ebo_->BufferData(0, indices.data(), indices.size() * sizeof(GLuint));
  vao_->LinkAttrib(*vbo_.get(), 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();
}

void SimpleLightModel::Render(Shader& shader) {
  shader.SetMat4("model", 1, false, model_matrix_);

  vao_->Bind();
  glDrawElements(GL_TRIANGLES, num_of_inidces_, GL_UNSIGNED_INT, 0);
  vao_->Unbind();
}
