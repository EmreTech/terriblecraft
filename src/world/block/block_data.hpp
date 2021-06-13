#ifndef BLOCK_DATA_HPP
#define BLOCK_DATA_HPP

#include <glad/glad.h>

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "block_id.hpp"

namespace World
{

struct BlockData
{
    block_t id = 0;
    
    std::string name;
    std::string topTexture, sideTexture, bottomTexture;

    GLuint topTexId = 0, sideTexId = 0, bottomTexId = 0;

    BlockMeshStyle style = BlockMeshStyle::Block;
    BlockType type = BlockType::Solid;

    bool collidable = true;
};

struct BlockDataManager
{
    BlockDataManager();
    void initCommonBlockTypes();

    block_t addBlock(const BlockData &data);

    const BlockData& getData(block_t id) const;
    const BlockData& getData(const std::string &name) const;

    block_t getId(CommonBlock block) const;
    block_t getId(const std::string &name) const;

    const std::vector<BlockData>& getAllData() const;

    private:
    std::vector<BlockData> blocks;
    std::vector<block_t> commonBlockIds;
    std::unordered_map<std::string, block_t> blockMap;
};

} // namespace World


#endif