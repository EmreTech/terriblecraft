#ifndef CHUNK_MESH_BUILDER_HPP
#define CHUNK_MESH_BUILDER_HPP

#include "chunk_mesh.hpp"

namespace World
{

struct BlockDataManager;
struct Chunk;

ChunkMesh buildChunkMesh(const Chunk &chunk, const BlockDataManager &blockData);

} // namespace World


#endif