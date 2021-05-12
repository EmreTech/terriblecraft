#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <string>

namespace gl {

struct Texture {
  unsigned int ID;
  int width, height;

  Texture() {}

  Texture(const std::string &filepath, GLint typeOfImage,
          int stbi_load_as = STBI_rgb) {
    init(filepath, typeOfImage, stbi_load_as);
  }

  void init(const std::string &filepath, GLint typeOfImage, int stbi_load_as);
  void bind();
};

} // namespace gl

#endif