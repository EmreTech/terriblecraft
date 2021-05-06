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

    Texture(const std::string &filepath, GLint typeOfImage, bool flipImage = false)
    {
        init(filepath, typeOfImage, flipImage);
    }

    void init(const std::string &filepath, GLint typeOfImage, bool flipImage);
};

} // namespace gl


#endif