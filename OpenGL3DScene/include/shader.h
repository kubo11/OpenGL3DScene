#ifndef OPENGL3DSCENE_SHADER_H_
#define OPENGL3DSCENE_SHADER_H_

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
 public:
   Shader(const std::string&);
   ~Shader();
   void Activate();
   const GLuint& GetID();

 private:
   GLuint ID_;
   std::string LoadShaderFile(const std::string&);
   void CheckShaderCompileErrors(GLuint);
   void CheckProgramCompileErrors(GLuint);
};

#endif  // OPENGL3DSCENE_SHADER_H_
