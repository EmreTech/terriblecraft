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

void Model::addMeshData(const Mesh& mesh)
{
    if (vao.ID != 0)
        deleteData();

    vao.init();

    addVBO(3, mesh.vertexPositions);
    addVBO(2, mesh.textureCoords);
    addEBO(mesh.indices);    
}

void Model::addVBO(int dimensions, const std::vector<float>& data)
{
    gl::Buffer vbo;
    vbo.init(GL_ARRAY_BUFFER);
    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(float), data);

    vao.attribute(vbo, vboCount, dimensions, GL_FLOAT, 0, 0);
    glEnableVertexAttribArray(vboCount++);

    buffers.push_back(vbo);
}

void Model::addEBO(const std::vector<unsigned int>& indices)
{
    gl::Buffer ebo;
    ebo.init(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int), indices);

    numOfIndices = indices.size();
}

void Model::deleteData()
{
    vao.destroy();
    for (auto& e : buffers)
        e.destroy();
    
    buffers.clear();

    vboCount = 0, numOfIndices = 0;
}