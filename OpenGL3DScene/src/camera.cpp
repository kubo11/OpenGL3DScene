#include "camera.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 orientation, bool free_movement, bool free_look) {
  position_ = position;
  orientation_ = orientation;
  free_movement_ = free_movement;
  free_look_ = free_look;
  view_matrix_ = glm::lookAt(position_, position_ + orientation_, up_);
}

void Camera::SetViewMatrix(Shader& shader) {
  view_matrix_ = glm::lookAt(position_, position_ + orientation_, up_);
  shader.SetMat4("view", 1, false, view_matrix_);
}

void Camera::Move(glm::vec3 move_vec) {
  if (!free_movement_) return;
  position_ += Speed * move_vec;
}

void Camera::MoveTo(glm::vec3 new_position) {
  position_ = new_position;
}

void Camera::Rotate(float rotX, float rotY) {
  if (!free_look_) return;
  glm::vec3 new_orientation = glm::rotate(orientation_, glm::radians(-rotX), glm::normalize(glm::cross(orientation_, up_)));

  if (abs(glm::angle(new_orientation, up_) - glm::radians(90.0f)) <= glm::radians(85.0f))
  {
    orientation_ = new_orientation;
  }

  orientation_ = glm::rotate(orientation_, glm::radians(-rotY), up_);
}

void Camera::Rotate(GLfloat angle, glm::vec3 axis) {
  orientation_ = glm::rotate(orientation_, glm::radians(angle), axis);
}

void Camera::LockMovement() {
  free_movement_ = false;
}

void Camera::UnlockMovement() {
  free_movement_ = true;
}

void Camera::LockLook() {
  free_look_ = false;
}

void Camera::UnlockLook() {
  free_look_ = true;
}

const glm::vec3& Camera::GetUp() const {
  return up_;
}

const glm::vec3& Camera::GetOrientation() const {
  return orientation_;
}

void Camera::SetOrientation(glm::vec3 orientation) {
  orientation_ = orientation;
}

const glm::vec3& Camera::GetPosition() const {
  return position_;
}
