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
}

void Model::addVBO(int dimensions, const std::vector<float>& data)
{
    std::cout << "Size of data: " << data.size() << '\n';
    gl::Buffer vbo;
    vbo.init(GL_ARRAY_BUFFER);
    vbo.bufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);

    vao.attribute(vbo, vboCount, dimensions, GL_FLOAT, 0, 0);
    glEnableVertexAttribArray(vboCount++);

    buffers.push_back(vbo);
}

void Model::deleteData()
{
    vao.destroy();
    for (auto& e : buffers)
        e.destroy();
    
    buffers.clear();

    vboCount = 0;
}