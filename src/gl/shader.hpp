#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../utils/glm_include.hpp"

namespace gl {

struct Shader {
  unsigned int ID;

  Shader() = default;

  Shader(const std::string vertexPath, const std::string fragPath) {
    init(vertexPath, fragPath);
  }

  void init(const std::string &vertexPath, const std::string &fragPath);

  void activate() { glUseProgram(ID); }

  void uniformInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void uniformMatrix4(const std::string &name, const glm::mat4& value) 
  {
      glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
  }

  void uniformVector3(const std::string &name, const glm::vec3 &value)
  {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
  }
};

} // namespace gl

#endif