#ifndef OPENGL3DSCENE_ERROR_LOG_H_
#define OPENGL3DSCENE_ERROR_LOG_H_

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#define ERROR std::cerr << "[" << fs::path(__FILE__).filename() << ":"  \
                        << __LINE__ << "] ERROR: "

#endif  // OPENGL3DSCENE_ERROR_LOG_H_
