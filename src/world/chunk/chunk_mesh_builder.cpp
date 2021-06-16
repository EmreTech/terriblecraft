#include "chunk_mesh_builder.hpp"

#include <iostream>

#include "chunk.hpp"
#include "../block/block_data.hpp"
#include "../../utils/texture_atlas.hpp"

namespace
{

using namespace ::World;

const MeshFace FRONT_FACE  = {{1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 4};
const MeshFace LEFT_FACE   = {{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 3};
const MeshFace BACK_FACE   = {{0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, 4};
const MeshFace RIGHT_FACE  = {{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 3};
const MeshFace TOP_FACE    = {{1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, 5};
const MeshFace BOTTOM_FACE = {{0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1}, 2};

bool makeFace(block_t thisID, block_t compare)
{
    auto &blockData = BlockDataManager::get();

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

ChunkMesh buildChunkMesh(const Chunk &chunk)
{
    auto &blockData = BlockDataManager::get();
    ChunkMesh mesh(chunk.getPosition());

    const float ROWS = 16.0f, COLUMNS = 16.0f;

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        Position blockPos(x, y, z);
        block_t block = chunk.quickGetBlock(blockPos);

        if (block != blockData.getId(CommonBlock::Air))
        {
            auto &blkData = blockData.getData(block);

            World::TextureData topTexCoords    = GetTextureCoords(blkData.topTextureCoords, COLUMNS, ROWS);
            World::TextureData sideTexCoords   = GetTextureCoords(blkData.sideTextureCoords, COLUMNS, ROWS);
            World::TextureData bottomTexCoords = GetTextureCoords(blkData.bottomTextureCoords, COLUMNS, ROWS);

            // Left
            if (makeFace(block, chunk.getBlock({x - 1, y, z})))
                mesh.addFace(LEFT_FACE, blockPos, sideTexCoords);

            // Right
            if (makeFace(block, chunk.getBlock({x + 1, y, z})))
                mesh.addFace(RIGHT_FACE, blockPos, sideTexCoords);

            // Front
            if (makeFace(block, chunk.getBlock({x, y, z + 1})))
                mesh.addFace(FRONT_FACE, blockPos, sideTexCoords);

            // Back
            if (makeFace(block, chunk.getBlock({x, y, z - 1})))
                mesh.addFace(BACK_FACE, blockPos, sideTexCoords);

            // Bottom
            if (makeFace(block, chunk.getBlock({x, y - 1, z})))
                mesh.addFace(BOTTOM_FACE, blockPos, bottomTexCoords);

            // Top
            if (makeFace(block, chunk.getBlock({x, y + 1, z})))
                mesh.addFace(TOP_FACE, blockPos, topTexCoords);
        }
    }

    return mesh;
}

} // namespace World
