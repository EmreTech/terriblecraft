#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <string>
#include <iostream>

namespace gl
{

struct Texture
{
    unsigned int ID;
    int width, height;

    Texture() {}

    Texture(const std::string &filepath, GLint typeOfImage, int stbi_load_as = STBI_rgb)
    {
        init(filepath, typeOfImage, stbi_load_as);
    }

    void init(const std::string &filepath, GLint typeOfImage, int stbi_load_as);
};

} // namespace gl


#endif