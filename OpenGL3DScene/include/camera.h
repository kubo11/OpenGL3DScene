#ifndef OPENGL3DSCENE_CAMERA_H_
#define OPENGL3DSCENE_CAMERA_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  glm::vec3 position;
  glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);;
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

  Camera(GLfloat, GLfloat, GLfloat, GLfloat, glm::vec3);
  Camera(Camera&) = delete;
  ~Camera() = default;

  void UpdateMatrices(GLuint, const char*);

private:
  GLfloat aspect_ratio_;
  GLfloat far_plane_;
  GLfloat fov_;
  GLfloat near_plane_;
};

#endif  // OPENGL3DSCENE_CAMERA_H_
