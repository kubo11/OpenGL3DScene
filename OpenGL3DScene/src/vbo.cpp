#include "vbo.h"

VBO::VBO(int num) {
  IDs_ = std::vector<GLuint>(num);
  glGenBuffers(num, IDs_.data());
}

VBO::~VBO() {
  glDeleteBuffers(IDs_.size(), IDs_.data());
}

void VBO::Bind(int id) {
  if (id > IDs_.size()) return;
  glBindBuffer(GL_ARRAY_BUFFER, IDs_[id]);
}

void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const std::vector<GLuint> VBO::GetIDs() {
  return IDs_;
}

void VBO::BufferData(int id, GLfloat vertices[], int size) {
  Bind(id);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}