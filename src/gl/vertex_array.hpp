#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <glad/glad.h>

#include <vector>

#include "../utils/singleton.hpp"

namespace gl
{

/**
 * @brief Information needed to draw with glDrawElements (indices)
 */
struct Drawable final
{
    Drawable(unsigned int vao, int indicesCount);

    void bindDraw(GLenum drawMode = GL_TRIANGLES) const;

    void bind() const;
    void draw(GLenum drawMode = GL_TRIANGLES) const;

    private:
    const unsigned int handle = 0;
    const int IndicesCount = 0;
};

/**
 * @brief New wrapper around the OpenGL vertex array object (shortened to VAO).
 * On top of wrapping the vao, it also wraps a buffer object like a vbo or ebo.
 */
struct VertexArray final : public NonCopyable
{
    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray &&other);
    VertexArray& operator=(VertexArray &&other);

    void create();
    void destroy();

    void bind() const;

    Drawable getDrawable() const;

    void addVBO(int mag, const std::vector<unsigned int> &data);
    void addVBO(int mag, const std::vector<float> &data);
    void addEBO(const std::vector<unsigned int> &indices);

    private:
    void reset();

    std::vector<unsigned int> buffers;
    unsigned int handle = 0;
    int indicesCount = 0;
};

} // namespace gl


#endif