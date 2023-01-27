#ifndef OPENGL3DSCENE_EBO_H_
#define OPENGL3DSCENE_EBO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class EBO {
public:
  EBO(int);
  ~EBO();

  EBO(const EBO&) = delete;
  EBO& operator = (const EBO&) = delete;

  EBO(EBO&&) noexcept = default;
  EBO& operator = (EBO&&) noexcept = default;

  void Bind(int);
  void Unbind();
  const std::vector<GLuint> GetIDs();
  void BufferData(int, GLuint[], int);

private:
  std::vector<GLuint> IDs_;
};

#endif  // OPENGL3DSCENE_EBO_H_