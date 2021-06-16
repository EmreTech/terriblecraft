#include "shader.hpp"

namespace
{

void shaderSuccessfullyCompiled(unsigned int ID, std::string_view type) {
  int success;
  char infoLog[512];
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(ID, 512, NULL, infoLog);
    std::cout << "Error while compiling the " << type << " shader: " << infoLog
              << '\n';
  }
}

void shaderSuccessfullyLinked(unsigned int ID) {
  int success;
  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "Error while linking the shaders: " << infoLog << '\n';
  }
}

} // namespace


namespace gl {

void Shader::init(const std::string &vertexPath, const std::string &fragPath) {
  // Read from provided vertex and fragment shader files
  std::string vertexCode, fragCode;
  std::ifstream vertexFile, fragFile;

  vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vertexFile.open(vertexPath);
    fragFile.open(fragPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vertexFile.rdbuf();
    fShaderStream << fragFile.rdbuf();

    vertexFile.close();
    fragFile.close();

    vertexCode = vShaderStream.str();
    fragCode = fShaderStream.str();
  } catch (const std::ifstream::failure e) {
    std::cout << "Error while reading shader files: " << e.what() << '\n';
  }

  // Compile the vertex and fragment shaders
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER),
               fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char *compileVertexCode = vertexCode.c_str(),
             *compileFragCode = fragCode.c_str();

  // Vertex Shader
  glShaderSource(vertexShader, 1, &compileVertexCode, NULL);
  glCompileShader(vertexShader);
  shaderSuccessfullyCompiled(vertexShader, "vertex");

  // Fragment Shader
  glShaderSource(fragShader, 1, &compileFragCode, NULL);
  glCompileShader(fragShader);
  shaderSuccessfullyCompiled(fragShader, "fragment");

  // Link the vertex and fragment shaders into a shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragShader);
  glLinkProgram(ID);
  shaderSuccessfullyLinked(ID);

  // Delete unneeded shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
}

} // namespace gl