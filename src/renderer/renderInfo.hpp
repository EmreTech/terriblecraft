#ifndef RENDERINFO_HPP
#define RENDERINFO_HPP

#include "../gl/vao.hpp"

struct RenderInfo
{
    gl::VAO vao;
    unsigned int indicesCount = 0;

    inline void reset()
    {
        vao.destroy();
        indicesCount = 0;
    }
};

#endif