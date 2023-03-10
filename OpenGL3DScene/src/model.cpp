#include "model.h"

#include <glm/gtc/matrix_transform.hpp>

Model::Model(const std::string& path, bool gamma) : gamma_correction_(gamma) {
  loadModel(path);
}

void Model::Draw(Shader& shader) {
  if (wiggle_angle_ != 0.0f) {
    glm::mat4 tmp = glm::rotate(model_matrix_, glm::radians(wiggle_angle_), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetMat4("model", 1, false, tmp);
  }
  else {
    shader.SetMat4("model", 1, false, model_matrix_);
  }
  for (int i = 0; i < meshes_.size(); ++i)
    meshes_[i].Draw(shader);
}

void Model::loadModel(const std::string& path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    ERROR << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    return;
  }

  directory_ = fs::absolute(fs::path(path).parent_path());
  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
  for (int i = 0; i < node->mNumMeshes; ++i) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(processMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<std::shared_ptr<Texture>> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;

    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }

    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;

      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;

      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.Tangent = vector;

      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
    }
    else {
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (int i = 0; i < mesh->mNumFaces; ++i)
  {
    aiFace face = mesh->mFaces[i];

    for (int j = 0; j < face.mNumIndices; ++j) {
      indices.push_back(face.mIndices[j]);
    }
  }

  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

  loadMaterialTextures(textures, material, aiTextureType_DIFFUSE, TextureType::kDiffuse);
  loadMaterialTextures(textures, material, aiTextureType_SPECULAR, TextureType::kSpecular);
  loadMaterialTextures(textures, material, aiTextureType_HEIGHT, TextureType::kNormal);
  loadMaterialTextures(textures, material, aiTextureType_AMBIENT, TextureType::kHeight);

  return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}

void Model::loadMaterialTextures(std::vector<std::shared_ptr<Texture>>& textures, aiMaterial* mat, aiTextureType type, TextureType texture_type) {
  for (int i = 0; i < mat->GetTextureCount(type); ++i) {
    aiString str;
    mat->GetTexture(type, i, &str);

    fs::path path = directory_ / fs::path(str.C_Str());
    auto texture = isTextureAlreadyLoaded(path);
    if (texture == nullptr) {
      texture = std::make_shared<Texture>(path.c_str(), texture_type);
      loaded_textures_.push_back(texture);
    }
    textures.push_back(texture);
  }
}

void Model::Translate(glm::vec3 translation_vec) {
  model_matrix_ = glm::translate(model_matrix_, translation_vec);
  for (auto& camera_connector : attached_cameras_) {
    camera_connector.camera->MoveTo(glm::vec3(model_matrix_ * glm::vec4(camera_connector.position, 1.0f)));
  }
  for (auto& spotlight_connector : attached_spotlights_) {
    spotlight_connector.light.MoveTo(glm::vec3(model_matrix_ * glm::vec4(spotlight_connector.position, 1.0f)));
  }
  for (auto& following_camera : following_cameras_) {
    following_camera->SetOrientation(glm::vec3(model_matrix_ * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) - following_camera->GetPosition());
  }
}

void Model::Scale(glm::vec3 scale) {
  model_matrix_ = glm::scale(model_matrix_, scale);
}

void Model::Rotate(GLfloat angle, glm::vec3 axis) {
  model_matrix_ = glm::rotate(model_matrix_, glm::radians(angle), axis);
  for (auto& camera_connector : attached_cameras_) {
    camera_connector.camera->Rotate(angle, axis);
  }
  for (auto& spotlight_connector : attached_spotlights_) {
    spotlight_connector.light.Rotate(angle, axis);
  }
}

std::shared_ptr<Texture> Model::isTextureAlreadyLoaded(fs::path path) {
  for (const auto& texture : loaded_textures_) {
    if (texture->GetPath() == path) return texture;
  }
  return nullptr;
}

void Model::AttachCamera(CameraConnector camera_connector) {
  attached_cameras_.push_back(camera_connector);
}

void Model::DettachCamera(std::shared_ptr<Camera> camera) {
  auto to_remove = std::find_if(attached_cameras_.begin(), attached_cameras_.end(), [&](CameraConnector cam) { return cam.camera == camera; });
  if (to_remove != attached_cameras_.end()) {
    attached_cameras_.erase(to_remove);
  }
}

void Model::AttachSpotlight(SpotLightConnector spotlight_connector) {
  attached_spotlights_.push_back(spotlight_connector);
}

void Model::AddFollowingCamera(std::shared_ptr<Camera> camera) {
  following_cameras_.push_back(camera);
}
void Model::RemoveFollowingCamera(std::shared_ptr<Camera> camera) {
  std::remove(following_cameras_.begin(), following_cameras_.end(), camera);
}

void Model::Wiggle() {
  wiggle_angle_ = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) - 5.0f);
}

void Model::Unwiggle() {
  wiggle_angle_ = 0.0f;
}

void Model::RotateLights(float rotX, float rotY) {
  for (auto& spotlight_connector : attached_spotlights_) {
    spotlight_connector.light.Rotate(rotX, rotY);
  }
}
