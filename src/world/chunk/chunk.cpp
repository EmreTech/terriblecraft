#include "chunk.hpp"

#include <iostream>

#include "../../renderer/chunkRenderer.hpp"

namespace World::Chunk
{

Chunk::Chunk(const glm::vec2 &pos) : position(pos) 
{}

void Chunk::makeMesh()
{
    for (auto& layer : chunks)
        layer.makeMesh();
}

void Chunk::deleteMeshes()
{
    for (auto& layer : chunks)
        layer.deleteMeshes();
}

void Chunk::draw(Renderer::ChunkRenderer& renderer)
{
    for (auto& layer : chunks)
    {
        if (!layer.buffered())
            layer.buffer();

        if (layer.getHasMesh() && layer.buffered())
            renderer.add(layer.mesh);
    }
}

void Chunk::addSection()
{
    int y = chunks.size();
    chunks.push_back(glm::vec3(position.x, y, position.y));
}

void Chunk::addSections(int index)
{
    while ((int) chunks.size() < index + 1)
        addSection();
}

void Chunk::addSectionsInBlocks(int blockY)
{
    int index = blockY / CHUNK_SIZE;
    addSections(index);
}

void Chunk::removeSection(int y)
{
    auto e = chunks.begin() + y;
    chunks.erase(e);
}

void Chunk::setBlock(int x, int y, int z, Block::Block b)
{
    addSectionsInBlocks(y);
    
    if (outOfBounds(x, y, z))
        return;

    int bY = y % CHUNK_SIZE;
    chunks.at(y / CHUNK_SIZE).setBlock(x, bY, z, b);
}

Block::Block Chunk::getBlock(int x, int y, int z) const noexcept
{
    if (outOfBounds(x, y, z))
        return Block::BlockType::AIR;

    int bY = y % CHUNK_SIZE;
    return chunks.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}

ChunkSection& Chunk::getSection(int index)
{
    static ChunkSection error({0, 0, 0});

    if (index >= (int) chunks.size() || index < 0)
        return error;

    return chunks.at(index);
}

const glm::vec2& Chunk::getPosition() const
{
    return position;
}

size_t Chunk::getAmountOfSections() const
{
    return chunks.size();
}

bool Chunk::outOfBounds(int x, int y, int z) const noexcept
{
    return yOutOfBound(y) || xzOutOfBound(x, z);
}

bool Chunk::yOutOfBound(int y) const noexcept
{
    if (y < 0)
        return true;

    if (y >= (int) chunks.size() * CHUNK_SIZE)
        return true;

    return false;
}

bool Chunk::xzOutOfBound(int x, int z) const noexcept
{
    if (x < 0 || z < 0)
        return true;

    if (x >= CHUNK_SIZE || z >= CHUNK_SIZE)
        return true;

    return false;
}

} // namespace World::Chunk
