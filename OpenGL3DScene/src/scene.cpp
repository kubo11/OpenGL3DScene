#include "scene.h"

void Scene::LoadData() {
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
  };
  GLuint indices[] = {
    0, 2, 1,
    0, 3, 2
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
}

void Scene::Render() {
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  shader_->Activate();
  texture_->Bind();
  vao_->Bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}