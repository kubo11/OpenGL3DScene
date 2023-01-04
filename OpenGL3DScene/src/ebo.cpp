#include "ebo.h"

EBO::EBO(int num) {
  IDs_ = std::vector<GLuint>(num);
  glGenBuffers(num, IDs_.data());
}

EBO::~EBO() {
  glDeleteBuffers(IDs_.size(), IDs_.data());
}

void EBO::Bind(int id) {
  if (id > IDs_.size()) return;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IDs_[id]);
}

void EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const std::vector<GLuint> EBO::GetIDs() {
  return IDs_;
}

void EBO::BufferData(int id, GLuint indices[], int size) {
  Bind(id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}