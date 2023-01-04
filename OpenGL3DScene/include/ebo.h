#ifndef OPENGL3DSCENE_EBO_H_
#define OPENGL3DSCENE_EBO_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class EBO {
public:
  EBO(int);
  EBO(EBO&) = delete;
  ~EBO();
  void Bind(int);
  void Unbind();
  const std::vector<GLuint> GetIDs();
  void BufferData(int, GLuint[], int);

private:
  std::vector<GLuint> IDs_;
};

#endif  // OPENGL3DSCENE_EBO_H_