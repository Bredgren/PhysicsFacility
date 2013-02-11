
#ifndef PHYSICSFACILICTYENGINE_SHADER_HPP
#define PHYSICSFACILICTYENGINE_SHADER_HPP

#include <string>
#include <vector>
#include <fstream>

#include <glew/glew.h>

// Function for loading shaders from files.
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif  // PHYSICSFACILICTYENGINE_SHADER_HPP
