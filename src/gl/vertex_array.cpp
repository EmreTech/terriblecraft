#include "vertex_array.hpp"

namespace
{

unsigned int generateBuffer(GLenum type = GL_ARRAY_BUFFER)
{
    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(type, vertexBuffer);
    return vertexBuffer;
}

template <typename T>
void buffer(const std::vector<T> &data, GLenum type = GL_ARRAY_BUFFER)
{
    glBufferData(type, data.size() * sizeof(T), &data.front(), GL_STATIC_DRAW);
}

void attribute(unsigned int index, int mag, GLenum type)
{
    glVertexAttribPointer(index, mag, type, GL_FALSE, 0, (void*)0);
}

void attributeInt(unsigned int index, int mag, GLenum type)
{
    glVertexAttribIPointer(index, mag, type, 0, (void*)0);
}

} // namespace

namespace gl
{

//////////////
// Drawable //
//////////////

Drawable::Drawable(unsigned int vao, int indicesCount)
: handle(vao), IndicesCount(indicesCount)
{}

void Drawable::bindDraw(GLenum drawMode) const
{
    bind();
    draw(drawMode);
}

void Drawable::bind() const
{
    glBindVertexArray(handle);
}

void Drawable::draw(GLenum drawMode) const
{
    glDrawElements(drawMode, IndicesCount, GL_UNSIGNED_INT, nullptr);
}

//////////////////
// Vertex Array //
//////////////////

VertexArray::VertexArray()
{
    create();
}

VertexArray::~VertexArray()
{
    destroy();
}

VertexArray::VertexArray(VertexArray &&other)
{
    *this = std::move(other);
}

VertexArray& VertexArray::operator=(VertexArray &&other)
{
    destroy();

    buffers = std::move(other.buffers);
    handle = other.handle;
    indicesCount = other.indicesCount;

    other.reset();
    return *this;
}

void VertexArray::create()
{
    if (!handle)
        glGenVertexArrays(1, &handle);
}

void VertexArray::destroy()
{
    if (handle)
        glDeleteVertexArrays(1, &handle);
}

void VertexArray::bind() const
{
    glBindVertexArray(handle);
}

Drawable VertexArray::getDrawable() const
{
    return {handle, indicesCount};
}

void VertexArray::addVBO(int mag, const std::vector<unsigned int> &data)
{
    bind();
    auto vBuffer = generateBuffer();
    buffer(data);
    attributeInt(buffers.size(), mag, GL_UNSIGNED_INT);
    glEnableVertexAttribArray(buffers.size());
    buffers.push_back(vBuffer);
}

void VertexArray::addVBO(int mag, const std::vector<float> &data)
{
    bind();
    auto vBuffer = generateBuffer();

    buffer(data);
    attribute(buffers.size(), mag, GL_FLOAT);
    glEnableVertexAttribArray(buffers.size());

    buffers.push_back(vBuffer);
}

void VertexArray::addEBO(const std::vector<unsigned int> &indices)
{
    bind();
    auto eBuffer = generateBuffer(GL_ELEMENT_ARRAY_BUFFER);

    buffer(indices, GL_ELEMENT_ARRAY_BUFFER);

    buffers.push_back(eBuffer);
    indicesCount = indices.size();
}

void VertexArray::reset()
{
    buffers.clear();
    handle = 0;
    indicesCount = 0;
}

} // namespace gl

