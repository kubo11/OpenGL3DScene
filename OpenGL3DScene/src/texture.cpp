#include "texture.h"

#include <stb/stb_image.h>

#include "error_log.h"

Texture::Texture(fs::path path, TextureType texture_type) : type_(texture_type), path_(path) {
  int width, height, colorChannels;

  //stbi_set_flip_vertically_on_load(true);

  unsigned char* bytes = stbi_load(path_.string().c_str(), &width, &height, &colorChannels, 0);
  if (!bytes) {
    ERROR << "Could not load texture at: " << path_.string() << std::endl;
    return;
  }

  GLenum format;
  switch (colorChannels) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    ERROR << "Unsupported pixel format detected in texture at: " << path_.string() << std::endl;
    return;
  }

  GL_CHECK(glGenTextures(1, &ID_));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, ID_));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, bytes));
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(bytes);
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture() {
  GL_CHECK(glDeleteTextures(1, &ID_));
}

void Texture::Bind() {
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, ID_));
}

void Texture::Unbind() {
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

const TextureType& Texture::GetType() const {
  return type_;
}

void Texture::Activate(unsigned int number) {
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + number));
}

void Texture::Deactivate() {
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
}

const fs::path Texture::GetPath() const {
  return path_;
}