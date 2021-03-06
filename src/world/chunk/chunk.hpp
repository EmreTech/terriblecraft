#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <array>

#include "chunk_mesh.hpp"
#include "../world_constants.hpp"
#include "../block/block_id.hpp"
#include "../../utils/glm_include.hpp"

namespace World
{

using BlockArray = std::array<block_t, CHUNK_VOLUME>;

struct ChunkManager;

struct Chunk
{
    Chunk(const glm::vec3 &position, ChunkManager &manager);
    
    /**
     * @brief Quickly gets a block - meaning if the block is out-of-bounds, 
     * we don't get the block from an adjacent chunk.
     * 
     * @param pos The position to get the block from
     * @return block_t The block's id at that position
     */
    block_t quickGetBlock(const glm::vec3 &pos) const;

    /**
     * @brief Quickly sets a block - meaning if the block is out-of-bounds, 
     * we don't set the block onto an adjacent chunk.
     * 
     * @param pos The position to set the block at
     * @param block The block to set
     */
    void quickSetBlock(const glm::vec3 &pos, block_t block);

    /**
     * @brief Gets a block at the provided position
     * This is a safe function, meaning out-of-bounds checking is done.
     * If the position is out-of-bounds, we get the block from a 
     * neighboring chunk.
     * 
     * @param pos The position to get the block from
     * @return block_t The block's id at that position
     */
    block_t getBlock(const glm::vec3 &pos) const;

    /**
     * @brief Sets a block at the provided position
     * This is a safe function, meaning out-of-bounds checking is done.
     * If the position is out-of-bounds, we set the block on a
     * neighboring chunk.
     * 
     * @param pos The position to set the block at
     * @param block The block to set
     */
    void setBlock(const glm::vec3 &pos, block_t block);

    const glm::vec3& getPosition() const;

    BlockArray blocks;

    private:
    glm::vec3 Position;
    ChunkManager *ptManager;
};

} // namespace World


#endif