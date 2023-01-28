#ifndef OPENGL3DSCENE_EBO_H_
#define OPENGL3DSCENE_EBO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class EBO {
public:
  EBO();
  ~EBO();

  EBO(const EBO&) = delete;
  EBO& operator = (const EBO&) = delete;

  EBO(EBO&&) noexcept = default;
  EBO& operator = (EBO&&) noexcept = default;

  void Bind();
  void Unbind();
  const GLuint GetID();
  void BufferData(void*, size_t);

private:
  GLuint ID_;
};

#endif  // OPENGL3DSCENE_EBO_H_