#ifndef OPENGL3DSCENE_CAMERA_H_
#define OPENGL3DSCENE_CAMERA_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Camera {
public:
  float Speed = 0.01f;

  Camera(glm::vec3, glm::vec3, bool=true, bool=true);
  ~Camera() = default;

  Camera(const Camera&) = delete;
  Camera& operator = (const Camera&) = delete;

  Camera(Camera&&) noexcept = default;
  Camera& operator = (Camera&&) noexcept = default;

  void SetViewMatrix(Shader&);
  void Move(glm::vec3);
  void MoveTo(glm::vec3);
  void Rotate(float, float);
  void Rotate(GLfloat, glm::vec3);
  void LockMovement();
  void UnlockMovement();
  void LockLook();
  void UnlockLook();
  const glm::vec3& GetUp() const;
  const glm::vec3& GetOrientation() const;
  const glm::vec3& GetPosition() const;

private:
  glm::vec3 position_;
  glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 orientation_;
  glm::mat4 view_matrix_ = glm::mat4(1.0f);
  bool free_movement_;
  bool free_look_;
};

#endif  // OPENGL3DSCENE_CAMERA_H_
