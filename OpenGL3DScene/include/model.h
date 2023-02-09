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
#include "light_source.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

namespace fs = std::filesystem;

struct CameraConnector {
  std::shared_ptr<Camera> camera;
  glm::vec3 position;

  CameraConnector(std::shared_ptr<Camera> camera, glm::vec3 position) : camera(camera), position(position) {}
};

struct SpotLightConnector {
  SpotLight& light;
  glm::vec3 position;

  SpotLightConnector(SpotLight& light, glm::vec3 position) : light(light), position(position) {}
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
  void AttachSpotlight(SpotLightConnector);
  void AddFollowingCamera(std::shared_ptr<Camera>);
  void RemoveFollowingCamera(std::shared_ptr<Camera>);
  void Wiggle();
  void Unwiggle();
  void RotateLights(float, float);

 private:
  std::vector<std::shared_ptr<Texture>> loaded_textures_;
  std::vector<CameraConnector> attached_cameras_;
  std::vector<SpotLightConnector> attached_spotlights_;
  std::vector<std::shared_ptr<Camera>> following_cameras_;
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
