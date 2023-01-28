#include "ebo.h"

#include "error_log.h"

EBO::EBO() {
  GL_CHECK(glGenBuffers(1, &ID_));
}

EBO::~EBO() {
  GL_CHECK(glDeleteBuffers(1, &ID_));
}

void EBO::Bind() {
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_));
}

void EBO::Unbind() {
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

const GLuint EBO::GetID() {
  return ID_;
}

void EBO::BufferData(void* indices, size_t size) {
  //Bind();
  GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}