#include "texture.hpp"

namespace gl
{

void Texture::init(const std::string &filepath, GLint typeOfImage, bool flipImage)
{
        // Generate the texture's ID
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // Generic settings for the textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load and generate the texture
        int nrChannels;

        if (flipImage)
            stbi_set_flip_vertically_on_load(true);
        else
            stbi_set_flip_vertically_on_load(false);

        unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, typeOfImage, width, height, 0, typeOfImage, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            std::cout << "Failed to load texture, your surroundings will be black." << '\n';

        // Free the data
        stbi_image_free(data);
}

} // namespace gl