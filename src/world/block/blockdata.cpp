#include "blockdata.hpp"

#include <fstream>
#include <iostream>

namespace World::Block {

BlockData::BlockData(const std::string &fName) {
  std::ifstream file;
  file.open("res/blocks/" + fName + ".block");

  if (!file.is_open())
  {
    std::cerr << "Error while reading file" << '\n';
  }

  std::cout << "res/blocks/" << fName << ".block" << '\n';


  std::string current_line;
  while (std::getline(file, current_line)) {
    if (current_line == "TexTop" || current_line == "TexSide" ||
        current_line == "TexBottom" || current_line == "TexAll") {
      int x, y;
      file >> x >> y;
      if (current_line == "TexTop")
        data.textureTop = glm::vec2(x, y);

      else if (current_line == "TexSide")
        data.textureSide = glm::vec2(x, y);

      else if (current_line == "TexBottom")
        data.textureBottom = glm::vec2(x, y);

      else if (current_line == "TexAll") {
        glm::vec2 restOfCoords = glm::vec2(x, y);
        data.textureTop = restOfCoords;
        data.textureSide = restOfCoords;
        data.textureBottom = restOfCoords;
      }
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
