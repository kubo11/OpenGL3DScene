#include "simple_model.h"

#include <glm/gtc/matrix_transform.hpp>

SimpleModel::SimpleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
  num_of_inidces_ = indices.size();
  vao_ = std::make_unique<VAO>();
  vbo_ = std::make_unique<VBO>();
  ebo_ = std::make_unique<EBO>();

  vao_->Bind();
  vbo_->Bind();
  vbo_->BufferData(vertices.data(), vertices.size() * sizeof(GLfloat));
  ebo_->Bind();
  ebo_->BufferData(indices.data(), indices.size() * sizeof(GLuint));

  vao_->LinkAttrib(*vbo_.get(), 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();
}

void SimpleModel::Draw(Shader& shader) {
  shader.SetMat4("model", 1, false, model_matrix_);

  vao_->Bind();
  GL_CHECK(glDrawElements(GL_TRIANGLES, num_of_inidces_, GL_UNSIGNED_INT, 0));
  vao_->Unbind();
}

void SimpleModel::Translate(glm::vec3 position) {
  model_matrix_ = glm::translate(model_matrix_, position);
}

void SimpleModel::Scale(glm::vec3 scale) {
  model_matrix_ = glm::scale(model_matrix_, scale);
}

void SimpleModel::Rotate(GLfloat angle, glm::vec3 axis) {
  model_matrix_ = glm::rotate(model_matrix_, angle, axis);
}
