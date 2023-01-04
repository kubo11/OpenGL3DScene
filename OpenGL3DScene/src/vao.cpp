#include "vao.h"

VAO::VAO() {
  glGenVertexArrays(1, &ID_);
}

VAO::~VAO() {
  glDeleteVertexArrays(1, &ID_);
}

void VAO::Bind() {
  glBindVertexArray(ID_);
}

void VAO::Unbind() {
  glBindVertexArray(0);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
}