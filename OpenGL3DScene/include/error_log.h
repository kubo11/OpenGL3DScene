#ifndef OPENGL3DSCENE_ERROR_LOG_H_
#define OPENGL3DSCENE_ERROR_LOG_H_

#include <iostream>
#include <filesystem>
#include <glad/glad.h>

namespace fs = std::filesystem;

#define ERROR std::cerr << "[" << fs::path(__FILE__).filename() << ":"  \
                        << __LINE__ << "] ERROR: "

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
    abort();
  }
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif


#endif  // OPENGL3DSCENE_ERROR_LOG_H_
