#include "block_data.hpp"

namespace World
{

BlockDataManager::BlockDataManager()
: commonBlockIds(static_cast<size_t>(CommonBlock::Size))
{
    // Just for testing

    BlockData air;
    air.name = "air";
    air.topTextureCoords = {0, 0};
    air.sideTextureCoords = {0, 0};
    air.bottomTextureCoords = {0, 0};
    air.style = BlockMeshStyle::None;
    air.type = BlockType::Gas;
    air.collidable = false;

    BlockData grass;
    grass.name = "grass";
    grass.topTextureCoords = {0, 0};
    grass.sideTextureCoords = {1, 0};
    grass.bottomTextureCoords = {2, 0};

    addBlock(air);
    addBlock(grass);

    initCommonBlockTypes();
}

BlockDataManager& BlockDataManager::get()
{
    static BlockDataManager bdm;
    return bdm;
}

void BlockDataManager::initCommonBlockTypes()
{
    auto addBlockToCommonBlocks = [&](CommonBlock block, const char *id)
    {
        commonBlockIds[static_cast<uint8_t>(block)] = getId(id);
    };

    addBlockToCommonBlocks(CommonBlock::Air,   "air");

    /*
    addBlockToCommonBlocks(CommonBlock::Stone, "stone");
    addBlockToCommonBlocks(CommonBlock::Sand,  "sand");
    addBlockToCommonBlocks(CommonBlock::Water, "water");
    */
}

block_t BlockDataManager::addBlock(const BlockData &data)
{
    blockMap.emplace(data.name, blocks.size());

    auto &dat = blocks.emplace_back(data);
    dat.id = static_cast<block_t>(blocks.size() - 1);

    return dat.id;
}

const BlockData& BlockDataManager::getData(block_t id) const
{
    return blocks.at(id);
}

const BlockData& BlockDataManager::getData(const std::string &name) const
{
    return blocks.at(getId(name));
}

block_t BlockDataManager::getId(CommonBlock block) const
{
    return commonBlockIds.at(static_cast<block_t>(block));
}

block_t BlockDataManager::getId(const std::string &name) const
{
    return blockMap.at(name);
}

const std::vector<BlockData>& BlockDataManager::getAllData() const
{
    return blocks;
}

} // namespace World
