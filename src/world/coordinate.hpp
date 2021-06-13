#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "../utils/glm_include.hpp"

using Position = glm::vec3;

struct PositionHash
{
    size_t operator()(const Position &position) const;
};

Position worldToChunkPosition(const Position &position);
Position toChunkPosition(const Position &position);
Position toLocalBlockPosition(const Position &position);
Position toGlobalBlockPosition(const Position &blockPos, const Position &localChunkPos);
Position toBlockPosition(const Position &vec);

#endif