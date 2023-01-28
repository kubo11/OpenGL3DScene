#ifndef OPENGL3DSCENE_MESH_H_
#define OPENGL3DSCENE_MESH_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "ebo.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
  glm::vec3 Tangent;
  glm::vec3 Bitangent;
  int m_BoneIDs[MAX_BONE_INFLUENCE];
  float m_Weights[MAX_BONE_INFLUENCE];
};

class Mesh {
 public:
  Mesh(std::vector<Vertex>, std::vector<GLuint>, std::vector<std::shared_ptr<Texture>>);
  ~Mesh() = default;

  Mesh(const Mesh&) = delete;
  Mesh& operator = (const Mesh&) = delete;

  Mesh(Mesh&&) noexcept = default;
  Mesh& operator = (Mesh&&) noexcept = default;

  void Draw(Shader&);

private:
  std::unique_ptr<EBO> ebo_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::vector<Vertex> vertices_;
  std::vector<GLuint> indices_;
  std::vector<std::shared_ptr<Texture>> textures_;
};

#endif  // OPENGL3DSCENE_MESH_H_
