#include "shader.h"

Shader::Shader(const fs::path& vertexPath, const fs::path& fragmentPath)
{

 // 1. retrieve the vertex/fragment source code from filePath
 std::string vertexCode;
 std::string fragmentCode;
 std::ifstream vShaderFile;
 std::ifstream fShaderFile;
 // ensure ifstream objects can throw exceptions:
 vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
 fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
 try
 {
  // open files
  vShaderFile.open(vertexPath);
  fShaderFile.open(fragmentPath);
  std::stringstream vShaderStream, fShaderStream;
  // read file's buffer contents into streams
  vShaderStream << vShaderFile.rdbuf();
  fShaderStream << fShaderFile.rdbuf();
  // close file handlers
  vShaderFile.close();
  fShaderFile.close();
  // convert stream into string
  vertexCode = vShaderStream.str();
  fragmentCode = fShaderStream.str();
 }
 catch (std::ifstream::failure e)
 {
  std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
 }

 initialize(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::Shader(const char* vShaderCode, const char* fShaderCode)
{
 initialize(vShaderCode,fShaderCode);
}


unsigned int Shader::id() const
{
 return m_id;
}

void Shader::use()
{
 glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value)
{
 glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
 glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
 glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

Shader* Shader::defaultColorShader()
{
 const char* vShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec2 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec4 vColor;\n"
  "uniform mat4 transform;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = transform * vec4(aPos,0.00f, 1.0f);\n"
  "   vColor = vec4(aColor, 1.0f);\n"
  "}\0";

 const char* fShaderSource = "#version 330 core\n"
  "in vec4 vColor;\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vColor;\n"
  "}\0";
 
 return new Shader(vShaderSource, fShaderSource);
}

Shader* Shader::defaultShader()
{
 const char* vShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec2 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos,0.00f, 1.0f);\n"
  "}\0";

 const char* fShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.00f,0.00f,0.00f,1.00f);\n"
  "}\0";

 return new Shader(vShaderSource, fShaderSource);
}

void Shader::initialize(const char* vShaderCode, const char* fShaderCode)
{
 initializeOpenGLFunctions();

 // 2. compile shaders
 unsigned int vertex, fragment;
 int success;
 char infoLog[512];

 // vertex Shader
 vertex = glCreateShader(GL_VERTEX_SHADER);
 glShaderSource(vertex, 1, &vShaderCode, NULL);
 glCompileShader(vertex);
 // print compile errors if any
 glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
 if (!success)
 {
  glGetShaderInfoLog(vertex, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
 };

 // fragment Shader
 fragment = glCreateShader(GL_FRAGMENT_SHADER);
 glShaderSource(fragment, 1, &fShaderCode, NULL);
 glCompileShader(fragment);
 // print compile errors if any
 glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
 if (!success)
 {
  glGetShaderInfoLog(fragment, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
 };

 // shader Program
 m_id = glCreateProgram();
 glAttachShader(m_id, vertex);
 glAttachShader(m_id, fragment);
 glLinkProgram(m_id);
 // print linking errors if any
 glGetProgramiv(m_id, GL_LINK_STATUS, &success);
 if (!success)
 {
  glGetProgramInfoLog(m_id, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
 }

 // delete the shaders as they're linked into our program now and no longer necessary
 glDeleteShader(vertex);
 glDeleteShader(fragment);
}

