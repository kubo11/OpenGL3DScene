#include "light_source.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

LightSource::LightSource(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
  : Color(color), Position(position), ambient_(ambient), diffuse_(diffuse), specular_(specular) {}

LightSource::~LightSource() {

}

void LightSource::SwitchOn() {
  is_on_ = true;
}

void LightSource::SwitchOff() {
  is_on_ = false;
}

void LightSource::ShowModel() {
  show_model_ = true;
}

void LightSource::HideModel() {
  show_model_ = false;
}

void LightSource::SetModel(std::unique_ptr<SimpleModel> model) {
  model_ = std::move(model);
  model_->Translate(Position);
  model_->Scale(glm::vec3(0.2f));
  ShowModel();
}

void LightSource::RenderModel(Shader& shader) {
  if (show_model_ && model_ != nullptr) {
    model_->Draw(shader);
  }
}

PointLight::PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
  : LightSource(color, position, ambient, diffuse, specular) {}

PointLight::~PointLight() {

}

void PointLight::Render(Shader& shader, int idx) {
  std::string base_name = "pointLights[" + std::to_string(idx) + "].";

  shader.SetVec3(base_name + "position", Position);
  shader.SetVec3(base_name + "ambient", ambient_);
  shader.SetVec3(base_name + "diffuse", diffuse_);
  shader.SetVec3(base_name + "specular", specular_);
  shader.SetVec3(base_name + "attenuationCoeff", attenuation_coeff_);
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 orientation)
  : LightSource(color, position, ambient, diffuse, specular), Orientation(orientation) {}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::Render(Shader& shader, int idx) {
  std::string base_name = "directionalLights[" + std::to_string(idx) + "].";

  shader.SetFloat(base_name + "brightness", Brightness);
  shader.SetVec3(base_name + "orientation", Orientation);
  shader.SetVec3(base_name + "ambient", ambient_);
  shader.SetVec3(base_name + "diffuse", diffuse_);
  shader.SetVec3(base_name + "specular", specular_);
}

SpotLight::SpotLight(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 orientation, float innerCutoff, float outerCutoff)
  : LightSource(color, position, ambient, diffuse, specular), Orientation(orientation), innerCutoff_(innerCutoff), outerCutoff_(outerCutoff) {}

SpotLight::~SpotLight() {

}

void SpotLight::Render(Shader& shader, int idx) {
  std::string base_name = "spotLights[" + std::to_string(idx) + "].";

  shader.SetVec3(base_name + "position", Position);
  shader.SetVec3(base_name + "orientation", Orientation);
  shader.SetVec3(base_name + "ambient", ambient_);
  shader.SetVec3(base_name + "diffuse", diffuse_);
  shader.SetVec3(base_name + "specular", specular_);
  shader.SetVec3(base_name + "attenuationCoeff", attenuation_coeff_);
  shader.SetFloat(base_name + "innerCutOff", innerCutoff_);
  shader.SetFloat(base_name + "outerCutOff", outerCutoff_);
}

void SpotLight::MoveTo(glm::vec3 new_position) {
  Position = new_position;
}

void SpotLight::Rotate(float rotX, float rotY) {
  glm::vec3 new_orientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, glm::vec3(0.0f, -1.0f, 0.0f))));

  if (abs(glm::angle(new_orientation, glm::vec3(0.0f, -1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f))
  {
    Orientation = new_orientation;
  }

  Orientation = glm::rotate(Orientation, glm::radians(-rotY), glm::vec3(0.0f, -1.0f, 0.0f));
}

void SpotLight::Rotate(GLfloat angle, glm::vec3 axis) {
  Orientation = glm::rotate(Orientation, glm::radians(angle), axis);
}
