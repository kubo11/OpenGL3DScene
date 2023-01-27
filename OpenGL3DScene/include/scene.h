#ifndef OPENGL3DSCENE_SCENE_H_
#define OPENGL3DSCENE_SCENE_H_

#include <memory>

#include "camera.h"
#include "light_source.h"
#include "model.h"
#include "shader.h"
#include "timer.h"

class Scene {
public:
  Scene();
  ~Scene();

  Scene(const Scene&) = delete;
  Scene& operator = (const Scene&) = delete;

  Scene(Scene&&) noexcept = default;
  Scene& operator = (Scene&&) noexcept = default;
  
  void Render();
  Camera* current_camera;
  Shader* current_shader;

 private:
  std::vector<Camera> cameras_;
  std::vector<Shader> shaders_;
  std::unique_ptr<Shader> light_source_shader_;
  std::unique_ptr<Timer> timer_;
  std::vector<Model> models_;
  std::vector<PointLight> point_lights_;
  std::vector<DirectionalLight> directional_lights_;
  std::vector<SpotLight> spot_lights_;
};

#endif  // OPENGL3DSCENE_SCENE_H_