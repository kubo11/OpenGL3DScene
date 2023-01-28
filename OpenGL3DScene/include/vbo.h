#ifndef OPENGL3DSCENE_VBO_H_
#define OPENGL3DSCENE_VBO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class VBO {
 public:
  VBO();
  ~VBO();

  VBO(const VBO&) = delete;
  VBO& operator = (const VBO&) = delete;

  VBO(VBO&&) noexcept = default;
  VBO& operator = (VBO&&) noexcept = default;

  void Bind();
  void Unbind();
  const GLuint GetID();
  void BufferData(void*, size_t);

 private:
   GLuint ID_;
};

#endif  // OPENGL3DSCENE_VBO_H_