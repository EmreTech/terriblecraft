#ifndef BLOCK_DATA_HPP
#define BLOCK_DATA_HPP

#include <glad/glad.h>
#include <SFML/System/Vector2.hpp>

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "block_id.hpp"
#include "../../utils/singleton.hpp"

namespace World
{

struct BlockData
{
    // Id for this block type, assigned by the BlockDataManager
    block_t id = 0;
    
    // Another "id" to get the specific id for the block type
    std::string name;

    // Information for the texture atlas in order to render properly

    sf::Vector2i topTextureCoords;
    sf::Vector2i sideTextureCoords;
    sf::Vector2i bottomTextureCoords;

    // BlockMeshStyles is for rendering stuff
    BlockMeshStyle style = BlockMeshStyle::Block;
    // BlockType is for some other logic, might be used for rendering
    BlockType type = BlockType::Solid;

    // Determines if the block is collidable or not 
    // (if it is a solid block, then the answer should be yes!)
    bool collidable = true;
};

struct BlockDataManager : public Singleton
{
    static BlockDataManager& get();

    void initCommonBlockTypes();

    block_t addBlock(const BlockData &data);

    const BlockData& getData(block_t id) const;
    const BlockData& getData(const std::string &name) const;

    block_t getId(CommonBlock block) const;
    block_t getId(const std::string &name) const;

    const std::vector<BlockData>& getAllData() const;

    private:
    BlockDataManager();

    std::vector<BlockData> blocks;
    std::vector<block_t> commonBlockIds;
    std::unordered_map<std::string, block_t> blockMap;
};

} // namespace World


#endif