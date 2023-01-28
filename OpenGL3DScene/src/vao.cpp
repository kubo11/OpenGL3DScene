#include "vao.h"

#include "error_log.h"

VAO::VAO() {
  GL_CHECK(glGenVertexArrays(1, &ID_));
}

VAO::~VAO() {
  GL_CHECK(glDeleteVertexArrays(1, &ID_));
}

void VAO::Bind() {
  GL_CHECK(glBindVertexArray(ID_));
}

void VAO::Unbind() {
  GL_CHECK(glBindVertexArray(0));
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
  GL_CHECK(glEnableVertexAttribArray(layout));
  GL_CHECK(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset));
}