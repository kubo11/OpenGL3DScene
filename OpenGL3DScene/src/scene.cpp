#include "scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene::Scene() {
  camera_ = std::make_unique<Camera>(1.0f, 45.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.5f, 2.0f));
  timer_ = std::make_unique<Timer>(0.01f, [&]() { modelRotation_ += 0.5f; });
}

void Scene::LoadData() {
  GLfloat vertices[] = {
    -0.5f,  0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 0.0f,
     0.5f,  0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.0f,  0.5f,   1.0f, 1.0f, 1.0f,   5.0f, 0.0f,
     0.0f,  0.8f,  0.0f,   1.0f, 1.0f, 1.0f,   2.5f, 5.0f,
  };
  GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
  };
  shader_ = std::make_unique<Shader>("default");
  vao_ = std::make_unique<VAO>();
  vao_->Bind();
  vbo_ = std::make_unique<VBO>(1);
  vbo_->BufferData(0, vertices, sizeof(vertices));
  ebo_ = std::make_unique<EBO>(1);
  ebo_->BufferData(0, indices, sizeof(indices));
  vao_->LinkAttrib(*vbo_.get(), 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_.get(), 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  vao_->LinkAttrib(*vbo_.get(), 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  texture_ = std::make_unique<Texture>("wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();

  glEnable(GL_DEPTH_TEST);
}

void Scene::Render() {
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader_->Activate();

  timer_->Tick();

  glm::mat4 model = glm::mat4(1.0f);
  //glm::mat4 view = glm::mat4(1.0f);
  //glm::mat4 proj = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(modelRotation_), glm::vec3(0.0f, 1.0f, 0.0f));
  //view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
  //proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

  int modelLoc = glGetUniformLocation(shader_->GetID(), "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  camera_->UpdateMatrices(shader_->GetID(), "camMatrix");
  //int viewLoc = glGetUniformLocation(shader_->GetID(), "view");
  //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  //int projLoc = glGetUniformLocation(shader_->GetID(), "proj");
  //glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

  texture_->Bind();
  vao_->Bind();
  glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}