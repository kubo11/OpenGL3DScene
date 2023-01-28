#include "vbo.h"

#include "error_log.h"

VBO::VBO() {
  GL_CHECK(glGenBuffers(1, &ID_));
}

VBO::~VBO() {
  GL_CHECK(glDeleteBuffers(1, &ID_));
}

void VBO::Bind() {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, ID_));
}

void VBO::Unbind() {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

const GLuint VBO::GetID() {
  return ID_;
}

void VBO::BufferData(void* vertices, size_t size) {
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}