#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace gl {

struct Shader {
  unsigned int ID;

  Shader(const std::string vertexPath, const std::string fragPath) {
    init(vertexPath, fragPath);
  }

  void init(const std::string &vertexPath, const std::string &fragPath);

  void activate() { glUseProgram(ID); }

  void uniformInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void uniformMatrix4(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
  }

private:
  void shaderSuccessfullyCompiled(unsigned int ID, std::string_view type);
};

} // namespace gl

#endif