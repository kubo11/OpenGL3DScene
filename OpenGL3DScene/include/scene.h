#ifndef OPENGL3DSCENE_SCENE_H_
#define OPENGL3DSCENE_SCENE_H_

#include <memory>

#include "ebo.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

class Scene {
public:
  Scene() = default;
  Scene(Scene&) = delete;
  
  void LoadData();
  void Render();

 private:
  std::unique_ptr<EBO> ebo_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::unique_ptr<Shader> shader_;
  std::unique_ptr<Texture> texture_;
};

#endif  // OPENGL3DSCENE_SCENE_H_