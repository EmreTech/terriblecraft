#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"
#include "utils/singleton.hpp"
#include "gl/buffer.hpp"
#include "renderer/renderInfo.hpp"

struct Model : public NonCopyable
{
    Model() = default;
    Model(const Mesh& mesh);
    ~Model();

    Model(Model &&other);
    Model &operator=(Model &&other);

    void addMeshData(const Mesh& mesh);
    void deleteData();

    void addVBO(int dimensions, const std::vector<float>& data);
    void bindVAO() const
    {
        renderInfo.vao.bind();
    }

    int getIndicesCount() const;
    const RenderInfo& getRenderInfo() const;

    private:
    RenderInfo renderInfo;

    void addEBO(const std::vector<unsigned int>& indices);

    int vboCount = 0;
    std::vector<gl::Buffer> buffers;
};

#endif