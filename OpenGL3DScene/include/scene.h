#ifndef OPENGL3DSCENE_SCENE_H_
#define OPENGL3DSCENE_SCENE_H_

#include <memory>

#include "camera.h"
#include "light_source.h"
#include "model.h"
#include "shader.h"
#include "timer.h"
#include "utils.h"

class Scene {
public:
  std::shared_ptr<Camera> current_camera;
  std::shared_ptr<Shader> current_shader;
  int fog_level_ = 0;
  static const int max_fog_level = 4;
  bool enable_wiggling = false;
  glm::vec4 day_color = glm::vec4(0.67f, 0.73f, 0.77f, 1.0f);
  glm::vec4 night_color = glm::vec4(0.0f, 0.06f, 0.12f, 1.0f);
  glm::vec4 background_color_interval = divide(subtract(day_color, night_color), 1000.0f);

  Scene();
  ~Scene();

  Scene(const Scene&) = delete;
  Scene& operator = (const Scene&) = delete;

  Scene(Scene&&) noexcept = default;
  Scene& operator = (Scene&&) noexcept = default;
  
  void Render();
  void SetCamera(unsigned int);
  void SetShader(unsigned int);

 private:
  glm::mat4 projection_matrix_ = glm::mat4(1.0f);
  std::vector<std::shared_ptr<Camera>> cameras_;
  std::vector<std::shared_ptr<Shader>> shaders_;
  std::unique_ptr<Shader> light_source_shader_;
  std::unique_ptr<Timer> timer_;
  std::unique_ptr<Timer> day_timer_;
  std::unique_ptr<Timer> night_timer_;
  std::vector<Model> models_;
  std::vector<PointLight> point_lights_;
  std::vector<DirectionalLight> directional_lights_;
  std::vector<SpotLight> spot_lights_;
  glm::vec4 background_color_ = day_color/*glm::vec4(0.07f, 0.13f, 0.17f, 1.0f)*/;
  bool is_day_ = true;
  double interval_ = 0.01;
};

#endif  // OPENGL3DSCENE_SCENE_H_