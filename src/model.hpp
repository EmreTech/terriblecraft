#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"
#include "utils/singleton.hpp"
#include "gl/buffer.hpp"
#include "gl/vao.hpp"

struct Model
{
    gl::VAO vao;
    int numOfIndices = 0;

    Model() = default;
    Model(const Mesh& mesh);
    ~Model();

    void addMeshData(const Mesh& mesh);
    void deleteData();

    void addVBO(int dimensions, const std::vector<float>& data);

    private:
    void addEBO(const std::vector<unsigned int>& indices);

    int vboCount = 0;
    std::vector<gl::Buffer> buffers;
};

#endif