#ifndef OPENGL3DSCENE_TEXTURE_H_
#define OPENGL3DSCENE_TEXTURE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture {
 public:
  Texture(const char*, GLenum, GLenum, GLenum, GLenum);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator = (const Texture&) = delete;

  Texture(Texture&&) noexcept = default;
  Texture& operator = (Texture&&) noexcept = default;

  void Bind();
  void Unbind();

 private:
  GLuint ID_;
  GLenum type_;
};

#endif  // OPENGL3DSCENE_TEXTURE_H_