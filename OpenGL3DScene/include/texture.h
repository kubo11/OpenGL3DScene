#ifndef OPENGL3DSCENE_TEXTURE_H_
#define OPENGL3DSCENE_TEXTURE_H_

#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace fs = std::filesystem;

enum class TextureType {
  kUnknown,
  kDiffuse,
  kSpecular,
  kHeight,
  kNormal
};

class Texture {
 public:
  Texture(fs::path, TextureType);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator = (const Texture&) = delete;

  Texture(Texture&&) noexcept = default;
  Texture& operator = (Texture&&) noexcept = default;

  void Bind();
  void Unbind();
  const TextureType& GetType() const;
  void Activate(unsigned int);
  void Deactivate();
  const fs::path GetPath() const;

 private:
  GLuint ID_;
  TextureType type_;
  fs::path path_;
};

#endif  // OPENGL3DSCENE_TEXTURE_H_