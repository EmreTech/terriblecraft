#include "chunk_mesh_builder.hpp"

#include "chunk.hpp"
#include "../block/block_data.hpp"

namespace
{

using namespace ::World;

const MeshFace FRONT_FACE  = {{1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 4};
const MeshFace LEFT_FACE   = {{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 3};
const MeshFace BACK_FACE   = {{0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, 4};
const MeshFace RIGHT_FACE  = {{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 3};
const MeshFace TOP_FACE    = {{1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, 5};
const MeshFace BOTTOM_FACE = {{0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1}, 2};

bool makeFace(const BlockDataManager &blockData, block_t thisID, block_t compare)
{
    block_t airBlock = blockData.getId(CommonBlock::Air);
    auto &cmpBlock = blockData.getData(compare);

    if (compare == airBlock) // If the compared block is air, which means the block face is exposed.
        return true;

    else if ((cmpBlock.type != BlockType::Solid) && (compare != thisID)) // This is mostly for water, since the water floor needs to be visible
        return true;

    return false;
}

} // namespace


namespace World
{

ChunkMesh buildChunkMesh(const Chunk &chunk, const BlockDataManager &blockData)
{
    ChunkMesh mesh(chunk.getPosition());

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        Position blockPos(x, y, z);
        block_t block = chunk.quickGetBlock(blockPos);

        if (block != blockData.getId(CommonBlock::Air))
        {
            auto &blkData = blockData.getData(block);

            // Left
            if (makeFace(blockData, block, chunk.getBlock({x - 1, y, z})))
                mesh.addFace(LEFT_FACE, blockPos, {});

            // Right
            if (makeFace(blockData, block, chunk.getBlock({x + 1, y, z})))
                mesh.addFace(RIGHT_FACE, blockPos, {});

            // Front
            if (makeFace(blockData, block, chunk.getBlock({x, y, z + 1})))
                mesh.addFace(FRONT_FACE, blockPos, {});

            // Back
            if (makeFace(blockData, block, chunk.getBlock({x, y, z - 1})))
                mesh.addFace(BACK_FACE, blockPos, {});

            // Bottom
            if (makeFace(blockData, block, chunk.getBlock({x, y - 1, z})))
                mesh.addFace(BOTTOM_FACE, blockPos, {});

            // Top
            if (makeFace(blockData, block, chunk.getBlock({x, y + 1, z})))
                mesh.addFace(TOP_FACE, blockPos, {});
        }
    }

    return mesh;
}

} // namespace World
