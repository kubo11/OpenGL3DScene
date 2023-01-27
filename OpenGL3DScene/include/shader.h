#ifndef OPENGL3DSCENE_SHADER_H_
#define OPENGL3DSCENE_SHADER_H_

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Shader {
 public:
   Shader(const std::string&);
   ~Shader();

   Shader(const Shader&) = delete;
   Shader& operator = (const Shader&) = delete;

   Shader(Shader&&) noexcept = default;
   Shader& operator = (Shader&&) noexcept = default;

   void Activate();
   const GLuint& GetID() const;
   void SetInt(const std::string&, int);
   void SetFloat(const std::string&, float);
   void SetVec3(const std::string&, glm::vec3);
   void SetMat4(const std::string&, int, bool, glm::mat4);

 private:
   GLuint ID_;
   std::string LoadShaderFile(const std::string&);
   void CheckShaderCompileErrors(GLuint);
   void CheckProgramCompileErrors(GLuint);
};

#endif  // OPENGL3DSCENE_SHADER_H_
