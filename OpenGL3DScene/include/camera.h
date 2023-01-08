#ifndef OPENGL3DSCENE_CAMERA_H_
#define OPENGL3DSCENE_CAMERA_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  glm::vec3 Position;
  glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
  float Speed = 0.001f;

  Camera(GLfloat, GLfloat, GLfloat, GLfloat, glm::vec3, bool=true);
  Camera(Camera&) = delete;
  ~Camera() = default;

  void UpdateMatrices(GLuint, const char*);
  void Move(glm::vec3);
  void Rotate(float, float);
  void Lock();
  void Unlock();

private:
  GLfloat aspect_ratio_;
  GLfloat far_plane_;
  GLfloat fov_;
  GLfloat near_plane_;
  bool is_static_;
};

#endif  // OPENGL3DSCENE_CAMERA_H_
