#include "mesh.h"

#include "error_log.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<Texture>> textures)
    : vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures)) {
  vao_ = std::make_unique<VAO>();
  vbo_ = std::make_unique<VBO>();
  ebo_ = std::make_unique<EBO>();

  vao_->Bind();
  vbo_->Bind();
  vbo_->BufferData(vertices_.data(), vertices_.size() * sizeof(Vertex));
  ebo_->Bind();
  ebo_->BufferData(indices_.data(), indices_.size() * sizeof(GLuint));

  vao_->LinkAttrib(*vbo_.get(), 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
  vao_->LinkAttrib(*vbo_.get(), 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  vao_->LinkAttrib(*vbo_.get(), 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
  /*vao_->LinkAttrib(*vbo_.get(), 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
  vao_->LinkAttrib(*vbo_.get(), 4, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
  vao_->LinkAttrib(*vbo_.get(), 5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
  vao_->LinkAttrib(*vbo_.get(), 6, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));*/

  vao_->Unbind();
}

void Mesh::Draw(Shader& shader) {
  for (int i = 0; i < textures_.size(); ++i) {
    textures_[i]->Activate(i);

    std::string name;
    switch (textures_[i]->GetType()) {
    case TextureType::kDiffuse:
      name = "material.diffuse";
      break;
    case TextureType::kSpecular:
      name = "material.specular";
      break;
    case TextureType::kHeight:
      name = "material.height";
      break;
    case TextureType::kNormal:
      name = "material.normal";
      break;
    default:
      return;
    }

    shader.SetInt(name, i);
    textures_[i]->Bind();
  }

  vao_->Bind();
  GL_CHECK(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0));
  vao_->Unbind();

  GL_CHECK(glActiveTexture(GL_TEXTURE0));
}
