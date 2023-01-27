#ifndef OPENGL3DSCENE_LIGHT_SOURCE_H_
#define OPENGL3DSCENE_LIGHT_SOURCE_H_

#include <glm/glm.hpp>
#include <memory>

#include "model.h"
#include "shader.h"

class LightSource {
 public:
  LightSource(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
  ~LightSource();

  LightSource(const LightSource&) = delete;
  LightSource& operator = (const LightSource&) = delete;

  LightSource(LightSource&&) noexcept = default;
  LightSource& operator = (LightSource&&) noexcept = default;

  void SwitchOn();
  void SwitchOff();
  void ShowModel();
  void HideModel();
  void SetModel(std::unique_ptr<SimpleLightModel>);
  virtual void Render(Shader&, int) = 0;
  void RenderModel(Shader&);

  glm::vec3 Color;
  glm::vec3 Position;

 protected:
  bool is_on_ = true;
  std::unique_ptr<SimpleLightModel> model_ = nullptr;
  bool show_model_ = false;
  glm::vec3 ambient_;
  glm::vec3 diffuse_;
  glm::vec3 specular_;
};

class PointLight : public LightSource {
public:
  PointLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
  ~PointLight();

  PointLight(const PointLight&) = delete;
  PointLight& operator = (const PointLight&) = delete;

  PointLight(PointLight&&) noexcept = default;
  PointLight& operator = (PointLight&&) noexcept = default;

  void Render(Shader&, int);

 protected:
  glm::vec3 attenuation_coeff_ = glm::vec3(1.0f, 0.22f, 0.20f);
};

class DirectionalLight : public LightSource {
 public:
   DirectionalLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
  ~DirectionalLight();

  DirectionalLight(const DirectionalLight&) = delete;
  DirectionalLight& operator = (const DirectionalLight&) = delete;

  DirectionalLight(DirectionalLight&&) noexcept = default;
  DirectionalLight& operator = (DirectionalLight&&) noexcept = default;

  glm::vec3 Orientation;

  void Render(Shader&, int);

 protected:
};

class SpotLight : public LightSource {
public:
  SpotLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float, float);
  ~SpotLight();

  SpotLight(const SpotLight&) = delete;
  SpotLight& operator = (const SpotLight&) = delete;

  SpotLight(SpotLight&&) noexcept = default;
  SpotLight& operator = (SpotLight&&) noexcept = default;

  glm::vec3 Orientation;

  void Render(Shader&, int);

 protected:
  float innerCutoff_;
  float outerCutoff_;
  glm::vec3 attenuation_coeff_ = glm::vec3(1.0f, 0.22f, 0.20f);
};

#endif  // OPENGL3DSCENE_LIGHT_SOURCE_H_