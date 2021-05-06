#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <glad/glad.h>

#include <vector>
#include "../utils/types.hpp"

namespace gl
{

struct Buffer
{
    unsigned int ID;

    Buffer(){}

    void init(GLenum type)
    {
        glGenBuffers(1, &ID);
        bind(type);
    }

    void bind(GLenum type)
    {
        glBindBuffer(type, ID);
    }

    void bufferData(GLenum type, size_t size, const void *data, bool dynamic = false)
    {
        bind(type);
        glBufferData(type, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    template <typename T>
    void bufferData(GLenum type, size_t size, std::vector<T> data, bool dynamic = false)
    {
        bind(type);
        glBufferData(type, size * data.size(), &data.front(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    void destroy()
    {
        glDeleteBuffers(1, &ID);
    }
};

} // namespace gl

#endif