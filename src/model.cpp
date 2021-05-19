#include "model.hpp"

#include <iostream>

Model::Model(const Mesh& mesh)
{
    addMeshData(mesh);
}

Model::~Model()
{
    deleteData();
}

Model::Model(Model &&other) :   
    renderInfo(other.renderInfo),
    vboCount(other.vboCount),
    buffers(std::move(other.buffers))
{
    other.renderInfo.reset();
    other.vboCount = 0;
}

Model &Model::operator=(Model &&other)
{
    renderInfo = other.renderInfo;
    vboCount = other.vboCount;
    buffers = std::move(other.buffers);

    other.renderInfo.reset();
    other.vboCount = 0;

    return *this;
}

void Model::addMeshData(const Mesh& mesh)
{
    if (renderInfo.vao.ID != 0)
        deleteData();

    renderInfo.vao.init();
    bindVAO();

    addVBO(3, mesh.vertexPositions);
    addVBO(2, mesh.textureCoords);
    addEBO(mesh.indices);    
}

void Model::addVBO(int dimensions, const std::vector<float>& data)
{
    gl::Buffer vbo;
    vbo.init(GL_ARRAY_BUFFER);
    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(float), data);

    renderInfo.vao.attribute(vbo, vboCount, dimensions, GL_FLOAT, 0, 0);
    glEnableVertexAttribArray(vboCount++);

    buffers.push_back(vbo);
}

int Model::getIndicesCount() const
{
    return renderInfo.indicesCount;
}

const RenderInfo& Model::getRenderInfo() const
{
    return renderInfo;
}

void Model::addEBO(const std::vector<unsigned int>& indices)
{
    gl::Buffer ebo;
    ebo.init(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int), indices);
    renderInfo.indicesCount = static_cast<unsigned int>(indices.size());
}

void Model::deleteData()
{
    if (renderInfo.vao.ID)    
        renderInfo.vao.destroy();

    if (buffers.size() > 0)
        for (auto& e : buffers)
            glDeleteBuffers(1, &e.ID);
    
    buffers.clear();
    buffers.shrink_to_fit();

    vboCount = 0;
    renderInfo.reset();
}