#ifndef OPENGL3DSCENE_VBO_H_
#define OPENGL3DSCENE_VBO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class VBO {
 public:
  VBO(int);
  ~VBO();

  VBO(const VBO&) = delete;
  VBO& operator = (const VBO&) = delete;

  VBO(VBO&&) noexcept = default;
  VBO& operator = (VBO&&) noexcept = default;

  void Bind(int);
  void Unbind();
  const std::vector<GLuint> GetIDs();
  void BufferData(int, GLfloat[], int);

 private:
   std::vector<GLuint> IDs_;
};

#endif  // OPENGL3DSCENE_VBO_H_