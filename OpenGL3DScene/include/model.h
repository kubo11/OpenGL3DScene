#ifndef OPENGL3DSCENE_MODEL_H_
#define OPENGL3DSCENE_MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "camera.h"
#include "ebo.h"
#include "error_log.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

namespace fs = std::filesystem;

struct CameraConnector {
  std::shared_ptr<Camera> camera;
  glm::vec3 position;

  CameraConnector(std::shared_ptr<Camera> camera, glm::vec3 position, bool free_look) : camera(camera), position(position) {}
};

class SimpleModel {
 public:
  SimpleModel() = default;
  SimpleModel(std::vector<GLfloat>, std::vector<GLuint>);
  ~SimpleModel() = default;

  SimpleModel(const SimpleModel&) = delete;
  SimpleModel& operator = (const SimpleModel&) = delete;

  SimpleModel(SimpleModel&&) noexcept = default;
  SimpleModel& operator = (SimpleModel&&) noexcept = default;

  void Draw(Shader&);
  void Translate(glm::vec3);
  void Scale(glm::vec3);
  void Rotate(GLfloat, glm::vec3);

 protected:
  std::unique_ptr<EBO> ebo_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::unique_ptr<Texture> texture_ = nullptr;
  glm::mat4 model_matrix_ = glm::mat4(1.0f);
  unsigned int num_of_inidces_ = 0;
};

class Model {
 public:
  Model(const std::string& path, bool gamma = false);
  ~Model() = default;

  Model(const Model&) = delete;
  Model& operator = (const Model&) = delete;

  Model(Model&&) noexcept = default;
  Model& operator = (Model&&) noexcept = default;

  void Draw(Shader& shader);
  void Translate(glm::vec3);
  void Scale(glm::vec3);
  void Rotate(GLfloat, glm::vec3);
  void AttachCamera(CameraConnector);
  void DettachCamera(std::shared_ptr<Camera>);
  void Wiggle();
  void Unwiggle();

 private:
  std::vector<std::shared_ptr<Texture>> loaded_textures_;
  std::vector<CameraConnector> attached_cameras_;
  std::vector<Mesh> meshes_;
  fs::path directory_;
  bool gamma_correction_;
  glm::mat4 model_matrix_ = glm::mat4(1.0f);
  float wiggle_angle_ = 0.0f;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
  void loadMaterialTextures(std::vector<std::shared_ptr<Texture>>&, aiMaterial* mat, aiTextureType type, TextureType texture_type);
  std::shared_ptr<Texture> isTextureAlreadyLoaded(fs::path);
};

#endif  // OPENGL3DSCENE_MODEL_H_
