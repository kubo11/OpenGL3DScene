#ifndef OPENGL3DSCENE_VAO_H_
#define OPENGL3DSCENE_VAO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vbo.h"

class VAO {
public:
  VAO();
  ~VAO();

  VAO(const VAO&) = delete;
  VAO& operator = (const VAO&) = delete;

  VAO(VAO&&) noexcept = default;
  VAO& operator = (VAO&&) noexcept = default;

  void Bind();
  void Unbind();
  void LinkAttrib(VBO&, GLuint, GLuint, GLenum, GLsizeiptr, void*);

private:
  GLuint ID_;
};

#endif  // OPENGL3DSCENE_VAO_H_
