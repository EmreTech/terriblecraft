#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <SFML/Graphics/Image.hpp>

#include <iostream>
#include <string>

namespace gl 
{

// TODO: Redo the texture wrapper (I can do a lot better with sf::Image)

struct Texture 
{
    unsigned int ID;

    Texture() = default;
    Texture(const std::string &filepath);
    Texture(sf::Image &img);

    ~Texture();

    void init();
    void init(const std::string &filepath);
    void init(sf::Image &img);
    void destroy();

    void changeTexture(const std::string &filepath);
    void changeTexture(sf::Image &img);

    void bind() const;
};

} // namespace gl

#endif