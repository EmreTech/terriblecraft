#include "blockdata.hpp"

#include <fstream>
#include <iostream>

namespace World::Block {

BlockData::BlockData(const std::string &fName) {
  std::ifstream file;
  file.open("res/blocks/" + fName + ".block");

  if (!file.is_open())
  {
    std::cout << "Error while reading file" << '\n';
  }

  std::string current_line;
  while (std::getline(file, current_line)) {
    if (current_line == "TexTop") {
        int x, y;
        file >> x >> y;
        data.textureTop = {x, y};
    }
    else if (current_line == "TexSide") {
        int x, y;
        file >> x >> y;
        data.textureSide = {x, y};
    }
    else if (current_line == "TexBottom") {
        int x, y;
        file >> x >> y;
        data.textureBottom = {x, y};
    }
    else if (current_line == "TexAll") {
        int x, y;
        file >> x >> y;
        data.textureTop = {x, y};
        data.textureSide = {x, y};
        data.textureBottom = {x, y};
    }
    else if (current_line == "Id") {
      block_t id;
      file >> id;
      data.id = static_cast<BlockType>(id);
    }

    else if (current_line == "Opaque")
      file >> data.isOpaque;
  }
}

} // namespace World::Block
