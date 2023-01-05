#include "texture.h"

#include <stb/stb_image.h>

Texture::Texture(const char* filename, GLenum type, GLenum slot, GLenum format, GLenum pixelType) {
  type_ = type;

  int width, height, colorChannels;

  stbi_set_flip_vertically_on_load(true);

  unsigned char* bytes = stbi_load(filename, &width, &height, &colorChannels, 4);

  glGenTextures(1, &ID_);
  glActiveTexture(slot);
  glBindTexture(type_, ID_);

  glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(type_, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);

  glGenerateMipmap(type_);

  stbi_image_free(bytes);
  Unbind();
}

Texture::~Texture() {
  glDeleteTextures(1, &ID_);
}

void Texture::Bind() {
  glBindTexture(type_, ID_);
}

void Texture::Unbind() {
  glBindTexture(type_, 0);
}