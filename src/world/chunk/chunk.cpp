#include "chunk.hpp"

namespace World::Chunk
{

Chunk::Chunk(const glm::vec2 &pos) : position(pos) 
{
    generate();
}

void Chunk::generate()
{
    if (!generated)
    {
        for (int i = 0; i < CHUNK_SIZE; i++)
            addLayer();

        for (int y = 0; y < layers.size(); y++)
        for (int x = 0; x < CHUNK_SIZE; x++)
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            Block::Block b;

            if (y == CHUNK_SIZE)
                b.id = static_cast<Block::block_t>(Block::BlockType::GRASS);

            else
                b.id = static_cast<Block::block_t>(Block::BlockType::DIRT);
        }

        generated = true;
    }
}

void Chunk::makeMesh(const Player::Camera &cam)
{
    for (auto& layer : layers)
        if (!layer.getHasMesh())
            layer.makeMesh();
}

void Chunk::addLayer()
{
    int y = layers.size();
    layers.push_back(glm::vec3(position.x, y, position.y));
}

void Chunk::removeLayer(int y)
{
    auto e = layers.begin() + y;
    layers.erase(e);
}

void Chunk::setBlock(int x, int y, int z, Block::Block b)
{}

} // namespace World::Chunk
