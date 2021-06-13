#include "texture.hpp"

namespace
{

void setTextureParameters(GLenum target = GL_TEXTURE_2D)
{
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

} // namespace


namespace gl
{

Texture::Texture(const std::string &filepath)
{
    init(filepath);
}

Texture::Texture(sf::Image &img)
{
    init(img);
}

Texture::~Texture()
{
    destroy();
}

void Texture::init()
{
    glGenTextures(1, &ID);
}

void Texture::init(const std::string &filepath)
{
    sf::Image img;
    if (!img.loadFromFile(filepath))
    {
        img.create(256, 256, nullptr);
        for (unsigned int x = 0; x < 256; x++)
        for (unsigned int y = 0; y < 256; y++)
        {
            img.setPixel(x, y, sf::Color::Black);
        }
    }

    init(img);
}

void Texture::init(sf::Image &img)
{
    init();
    changeTexture(img);
}

void Texture::destroy()
{
    glDeleteTextures(1, &ID);
}

void Texture::changeTexture(const std::string &filepath)
{
    sf::Image img;
    if (!img.loadFromFile(filepath))
    {
        img.create(256, 256, nullptr);
        for (unsigned int x = 0; x < 256; x++)
        for (unsigned int y = 0; y < 256; y++)
        {
            img.setPixel(x, y, sf::Color::Black);
        }
    }

    changeTexture(img);
}

void Texture::changeTexture(sf::Image &img)
{
    bind();
    setTextureParameters();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA,
    GL_UNSIGNED_BYTE, img.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() const
{ 
    glBindTexture(GL_TEXTURE_2D, ID); 
}

} // namespace gl