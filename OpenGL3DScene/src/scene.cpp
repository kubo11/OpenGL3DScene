#include "scene.h"

#include <vector>

Scene::Scene() {
  projection_matrix_ = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.f);

  std::vector<GLfloat> lightVertices = {
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
  };
  std::vector<GLuint> lightIndices = {
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    4, 6, 7,
    0, 4, 5,
    0, 1, 5,
    1, 5, 6,
    1, 2, 6,
    2, 6, 7,
    2, 3, 7,
    3, 7, 4,
    3, 0, 4
  };

  cameras_.push_back(std::make_shared<Camera>(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
  cameras_.push_back(std::make_shared<Camera>(glm::vec3(0.2f, 0.3f, 2.1f), glm::vec3(0.0f, 0.0f, 1.0f), false, false));
  cameras_.push_back(std::make_shared<Camera>(glm::vec3(), glm::vec3(0.85f, -0.15f, 0.45f), false, true));
  cameras_.push_back(std::make_shared<Camera>(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(), false, false));
  current_camera = cameras_.front();

  models_.emplace_back("dingus/dingus.obj");
  models_.back().Scale(glm::vec3(0.02f, 0.02f, 0.02f));
  models_.back().Translate(glm::vec3(0.0f, 0.0f, 100.0f));
  models_.back().Rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  models_.back().AttachCamera(CameraConnector(cameras_[1], glm::vec3(15.0f, 15.0f, 10.0f), false));
  models_.back().AttachCamera(CameraConnector(cameras_[2], glm::vec3(-70.0f, 40.0f, -40.0f), false));
  models_.back().AddFollowingCamera(cameras_[3]);

  models_.emplace_back("floor/floor.obj");
  models_.back().Scale(glm::vec3(2.0f, 2.0f, 2.0f));
  models_.back().Translate(glm::vec3(0.0f, -0.1f, 0.0f));

  timer_ = std::make_unique<Timer>(0.01, [&]() { models_.front().Rotate(0.5f, glm::vec3(0.0f, 1.0f, 0.0f)); models_.front().Translate(glm::vec3(1.0f, 0.0f, 0.0f)); });
  day_timer_ = std::make_unique<Timer>(interval_, [&]() { 
    if (!compare(background_color_, night_color, 1e-5f)) { 
      background_color_ = subtract(background_color_, background_color_interval);
      directional_lights_.front().Brightness -= 9e-4f;
      directional_lights_.front().Orientation += glm::vec3(1e-3f, 1e-3f, 0.0f);
    } 
    else { 
      is_day_ = false;
      directional_lights_.front().Brightness = 0.1f;
      directional_lights_.front().Orientation = glm::vec3(-1.0f, 0.0f, 0.0f);
    } 
  });
  night_timer_ = std::make_unique<Timer>(interval_, [&]() { 
    if (!compare(background_color_, day_color, 1e-5f)) { 
      background_color_ = add(background_color_, background_color_interval);
      directional_lights_.front().Brightness += 9e-4f;
      directional_lights_.front().Orientation += glm::vec3(1e-3f, -1e-3f, 0.0f);
    }
    else { 
      is_day_ = true;
      directional_lights_.front().Brightness = 1.0f;
      directional_lights_.front().Orientation = glm::vec3(0.0f, -1.0f, 0.0f);
    } 
  });

  shaders_.push_back(std::make_shared<Shader>("phong_light"));
  shaders_.push_back(std::make_shared<Shader>("gouraud_light"));
  current_shader = shaders_.front();
  light_source_shader_ = std::make_unique<Shader>("light");

  point_lights_.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
  point_lights_.front().SetModel(std::make_unique<SimpleModel>(lightVertices, lightIndices));
  spot_lights_.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -0.5f, 1.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
  spot_lights_.front().SetModel(std::make_unique<SimpleModel>(lightVertices, lightIndices));
  directional_lights_.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));

  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

Scene::~Scene() {

}

void Scene::Render() {
  glClearColor(background_color_.x, background_color_.y, background_color_.z, background_color_.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  timer_->Tick();
  if (is_day_) {
    day_timer_->Tick();
  }
  else {
    night_timer_->Tick();
  }

  current_shader->Activate();

  current_shader->SetMat4("projection", 1, false, projection_matrix_);

  current_camera->SetViewMatrix(*current_shader);
  current_shader->SetVec3("viewPos", current_camera->GetPosition());

  current_shader->SetFloat("fogLevel", fog_level_);

  for (int i = 0; i < directional_lights_.size(); ++i) {
    directional_lights_[i].Render(*current_shader, i);
  }
  current_shader->SetInt("directionalLightsCount", directional_lights_.size());
  for (int i = 0; i < point_lights_.size(); ++i) {
    point_lights_[i].Render(*current_shader, i);
  }
  current_shader->SetInt("pointLightsCount", point_lights_.size());
  for (int i = 0; i < spot_lights_.size(); ++i) {
    spot_lights_[i].Render(*current_shader, i);
  }
  current_shader->SetInt("spotLightsCount", spot_lights_.size());

  if (enable_wiggling) {
    models_.front().Wiggle();
  }
  else {
    models_.front().Unwiggle();
  }

  for (auto& model : models_) {
    model.Draw(*current_shader);
  }

  light_source_shader_->Activate();
  light_source_shader_->SetMat4("projection", 1, false, projection_matrix_);
  current_camera->SetViewMatrix(*light_source_shader_.get());

  for (int i = 0; i < directional_lights_.size(); ++i) {
    directional_lights_[i].RenderModel(*light_source_shader_.get());
  }
  for (int i = 0; i < point_lights_.size(); ++i) {
    point_lights_[i].RenderModel(*light_source_shader_.get());
  }
  for (int i = 0; i < spot_lights_.size(); ++i) {
    spot_lights_[i].RenderModel(*light_source_shader_.get());
  }
}

void Scene::SetCamera(unsigned int num) {
  if (num >= cameras_.size()) return;
  current_camera = cameras_[num];
}

void Scene::SetShader(unsigned int num) {
  if (num >= shaders_.size()) return;
  current_shader = shaders_[num];
}
