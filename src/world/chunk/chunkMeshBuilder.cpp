#include "chunkMeshBuilder.hpp"

#include <iostream>

#include "chunkMesh.hpp"
#include "../block/blockatlas.hpp"
#include "../block/blockdata.hpp"
#include "../block/block.hpp"

namespace World::Chunk
{

namespace
{
    const std::vector<GLfloat> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };

    const std::vector<GLfloat> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
    };

    const std::vector<GLfloat> leftFace
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
    };

    const std::vector<GLfloat> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,
    };

    const std::vector<GLfloat> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
    };

    const std::vector<GLfloat> bottomFace
    {
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };  

} // namespace

// This is for testing nearby blocks to the current one to see which faces need to be renderered.
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

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk) : pChunk(&chunk) {}

int faces = 0;

void ChunkMeshBuilder::buildMesh(ChunkMesh& mesh)
{
    pMesh = &mesh;
    AdjacentBlockPositions directions;

    //std::cout << "Start chunk mesh build" << '\n';

    for (float i = 0; i < CHUNK_VOLUME; i++)
    {
        float x = (int) i % CHUNK_SIZE;
        float y = (int) i / CHUNK_AREA;
        float z = ((int) i / CHUNK_SIZE) % CHUNK_SIZE;

        if (!makeLayer(y))
            continue;

        glm::vec3 position(x, y, z);
        Block::Block b = pChunk->getBlock(x, y, z);

        if (b == Block::BlockType::AIR)
            continue;

        pBlockData = &b.getData().getData();
        auto& data = *pBlockData;
        directions.update(x, y, z);

        addFace(backFace,   data.textureSide,   position, directions.back);
        addFace(frontFace,  data.textureSide,   position, directions.front);

        addFace(rightFace,  data.textureSide,   position, directions.right);
        addFace(leftFace,   data.textureSide,   position, directions.left);

        addFace(topFace,    data.textureTop,    position, directions.up);
        addFace(bottomFace, data.textureBottom, position, directions.down);
    }

    //std::cout << "Finish chunk mesh build!" << '\n';
}

void ChunkMeshBuilder::addFace(const std::vector<float>& blockFace,
                const glm::vec2& textureCoords,
                const glm::vec3& blockPos,
                const glm::vec3& blockFacing)
{
    if (makeFace(blockFacing))
    {
        faces++;
        auto texCoords = World::Block::GetTextureCoords(textureCoords.x, textureCoords.y);

        pMesh->addFace(blockFace, texCoords, pChunk->getPosition(), blockPos);
    }
}

bool ChunkMeshBuilder::makeFace(const glm::vec3& blockPos)
{
    auto block = pChunk->getBlock(blockPos.x, blockPos.y, blockPos.z);
    auto& data = block.getData().getData();
    
    if (block == Block::BlockType::AIR)
        return true;

    else if ((!data.isOpaque) && (data.id != pBlockData->id))
        return true;

    return false;
}

bool ChunkMeshBuilder::makeLayer(int y)
{
    return (!pChunk->getLayer(y).isAllSolid()) ||
            (!pChunk->getLayer(y + 1).isAllSolid()) ||
            (!pChunk->getLayer(y - 1).isAllSolid());
}

} // namespace World::Chunk
