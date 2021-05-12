#include "chunkMeshBuilder.hpp"

#include <iostream>

#include "layer.hpp"
#include "chunkMesh.hpp"
#include "../block/blockatlas.hpp"
#include "../block/blockdata.hpp"
#include "../block/block.hpp"

namespace World::Chunk
{

namespace
{

std::vector<float> backFace
{
    0.0f, 0.0f, 0.0f, // Bottom-left
    1.0f, 1.0f, 0.0f,   // top-right
    1.0f, 0.0f, 0.0f,  // bottom-right
    1.0f, 1.0f, 0.0f,   // top-right
    0.0f, 0.0f, 0.0f, // bottom-left
    0.0f, 1.0f, 0.0f,  // top-left
};

std::vector<float> frontFace
{
    0.0f, 0.0f, 1.0f, // bottom-left
    1.0f, 0.0f, 1.0f,  // bottom-right
    1.0f, 1.0f, 1.0f,   // top-right
    1.0f, 1.0f, 1.0f,   // top-right
    0.0f, 1.0f, 1.0f,  // top-left
    0.0f, 0.0f, 1.0f, // bottom-left
};

std::vector<float> leftFace
{
    0.0f, 1.0f, 1.0f,   // top-right
    0.0f, 1.0f, 0.0f,  // top-left
    0.0f, 0.0f, 0.0f, // bottom-left
    0.0f, 0.0f, 0.0f, // bottom-left
    0.0f, 0.0f, 1.0f,  // bottom-right
    0.0f, 1.0f, 1.0f,   // top-right
};

std::vector<float> rightFace
{
    1.0f, 1.0f, 1.0f,    // top-left
    1.0f, 0.0f, 0.0f,  // bottom-right
    1.0f, 1.0f, 0.0f,   // top-right
    1.0f, 0.0f, 0.0f,  // bottom-right
    1.0f, 1.0f, 1.0f,    // top-left
    1.0f, 0.0f, 1.0f,   // bottom-left
};

std::vector<float> bottomFace
{
    0.0f, 0.0f, 0.0f, // top-right
    1.0f, 0.0f, 0.0f,  // top-left
    1.0f, 0.0f, 1.0f,   // bottom-left
    1.0f, 0.0f, 1.0f,   // bottom-left
    0.0f, 0.0f, 1.0f,  // bottom-right
    0.0f, 0.0f, 0.0f, // top-right
};

std::vector<float> topFace
{
    0.0f, 1.0f, 0.0f, // top-left
    1.0f, 1.0f, 1.0f,   // bottom-right
    1.0f, 1.0f, 0.0f,  // top-right
    1.0f, 1.0f, 1.0f,   // bottom-right
    0.0f, 1.0f, 0.0f, // top-left
    0.0f, 1.0f, 1.0f,  // bottom-left
};

} // namespace

struct AdjacentBlockPositions
{
    void update(int x, int y, int z)
    {
        up      =   {x,     y + 1,  z};
        down    =   {x,     y - 1,  z};
        left    =   {x - 1, y,      z};
        right   =   {x + 1, y,      z};
        front   =   {x,     y,      z + 1};
        back    =   {x,     y,      z - 1};
    }

    glm::vec3 up;
    glm::vec3 down;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 back;
};

ChunkMeshBuilder::ChunkMeshBuilder(Layer& chunk) : pLayer(&chunk) {}

int faces = 0;

void ChunkMeshBuilder::buildMesh(ChunkMesh& mesh)
{
    pMesh = &mesh;
    AdjacentBlockPositions directions;

    std::cout << "Start chunk mesh build" << '\n';

    for (float x = 0.0f; x < CHUNK_SIZE; x++)
    for (float z = 0.0f; z < CHUNK_SIZE; z++)
    {
        glm::vec3 position(x, 0, z);
        Block::Block b = pLayer->getBlock(x, z);

        if (b == Block::BlockType::AIR)
            continue;

        pBlockData = &b.getData().getData();
        auto& data = *pBlockData;

        float tmpXone = x + 1;
        float tmpZone = z + 1;
        float tmpXtwo = x - 1;
        float tmpZtwo = z - 1;

        if ( !((tmpXone >= CHUNK_SIZE || tmpZone >= CHUNK_SIZE) || (tmpXtwo < 0 || tmpZtwo < 0)) )
            directions.update(x, 0, z);

        addFace(bottomFace, data.textureBottom, position, directions.down);
        addFace(topFace, data.textureTop, position, directions.up);

        addFace(leftFace, data.textureSide, position, directions.left);
        addFace(rightFace, data.textureSide, position, directions.right);

        addFace(frontFace, data.textureSide, position, directions.front);
        addFace(backFace, data.textureSide, position, directions.back);
    }

    std::cout << "Finish chunk mesh build!" << '\n';
}

// TODO: Move this to utils somewhere
std::vector<float> vecTwoToFloat(std::array<glm::vec2, 6> vec)
{
    std::vector<float> output;
    for (size_t i{0}; i < vec.size(); i++)
    {
        auto cx = vec.at(i).x;
        auto cy = vec.at(i).y;

        output.push_back(cx);
        output.push_back(cy);
    }
    return output;
}

void ChunkMeshBuilder::addFace(const std::vector<float>& blockFace,
                const glm::vec2& textureCoords,
                const glm::vec3& blockPos,
                const glm::vec3& blockFacing)
{
    if (makeFace(blockFacing))
    {
        auto texCoords = vecTwoToFloat(World::Block::GetTextureCoords(textureCoords.x, textureCoords.y, faces % 6)); 
        faces++;
        pMesh->addFace(blockFace, texCoords, pLayer->getPosition(), blockPos);
    }
}

bool ChunkMeshBuilder::makeFace(const glm::vec3& blockPos)
{
    auto block = pLayer->getBlock(blockPos.x, blockPos.z);

    if (block == Block::BlockType::AIR)
        return true;

    else
        return false;
}

} // namespace World::Chunk
