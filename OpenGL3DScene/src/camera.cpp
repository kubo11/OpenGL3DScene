#include "camera.h"

Camera::Camera(GLfloat aspect_ratio, GLfloat fov, GLfloat near_plane, GLfloat far_plane, glm::vec3 position) {
  aspect_ratio_ = aspect_ratio;
  fov_ = fov;
  near_plane_ = near_plane;
  far_plane_ = far_plane;
  this->position = position;
}

void Camera::UpdateMatrices(GLuint shader_id, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(position, position + direction, up);
	proj = glm::perspective(glm::radians(fov_), aspect_ratio_, near_plane_, far_plane_);

	glUniformMatrix4fv(glGetUniformLocation(shader_id, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}