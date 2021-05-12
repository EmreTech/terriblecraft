#ifndef BLOCKDATA_HPP
#define BLOCKDATA_HPP

#include <glm/vec2.hpp>

#include <string>
#include <vector>

#include "../../utils/singleton.hpp"
#include "blockid.hpp"

namespace World::Block {

/**
 * @brief Stores simple data for a block.
 */
struct BlockDataHolder : public NonCopyable {
  // The block's id/type
  BlockType id;

  // Texture coordinates for the texture atlas system if the block has multiple
  // textures
  glm::vec2 textureTop, textureSide, textureBottom;

  // If the block is opaque or not
  bool isOpaque;
};

struct BlockData : public NonCopyable {
  BlockData(const std::string &fName);
  const BlockDataHolder &getData() const { return data; }

private:
  BlockDataHolder data;
};

} // namespace World::Block

#endif