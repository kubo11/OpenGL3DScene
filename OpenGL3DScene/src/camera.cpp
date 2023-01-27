#include "camera.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(GLfloat aspect_ratio, GLfloat fov, GLfloat near_plane, GLfloat far_plane, glm::vec3 position, bool is_static) {
  aspect_ratio_ = aspect_ratio;
  fov_ = fov;
  near_plane_ = near_plane;
  far_plane_ = far_plane;
  Position = position;
  is_static_ = is_static;
}

void Camera::UpdateMatrices(Shader& shader) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(fov_), aspect_ratio_, near_plane_, far_plane_);

  shader.SetMat4("camMatrix", 1, false, proj * view);
}

void Camera::Move(glm::vec3 moveVec) {
  if (is_static_) return;
  Position += Speed * moveVec;
}

void Camera::Rotate(float rotX, float rotY) {
  if (is_static_) return;
  glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

  if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
  {
    Orientation = newOrientation;
  }

  Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
}

void Camera::Lock() {
  is_static_ = true;
}

void Camera::Unlock() {
  is_static_ = false;
}
