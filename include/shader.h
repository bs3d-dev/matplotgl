#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "qopenglfunctions_3_3_core.h"

namespace fs = std::filesystem;


class Shader : protected QOpenGLFunctions_3_3_Core
{
public:

 // constructor reads and builds the shader
 explicit Shader(const fs::path& vertexPath, const fs::path& fragmentPath);
 Shader(const char* vertexCode, const char* fragmentCode);
 // use/activate the shader
 unsigned int id() const;
 void use();
 // utility uniform functions
 void setBool(const std::string& name, bool value);
 void setInt(const std::string& name, int value);
 void setFloat(const std::string& name, float value);

 static Shader* defaultColorShader();
 static Shader* defaultShader();
 static Shader* gridShader();

private:
 void initialize(const char* vertexCode, const char* fragmentCode);

private:
 // the program ID
 unsigned int m_id;
};

#endif
