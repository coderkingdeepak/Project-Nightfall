#pragma once

#include "Vector3.h"
#include <array>
#include <vector>

class PathfindingSystem
{
public:
    static constexpr int GRID_SIZE = 25;

    PathfindingSystem();

    void SetBlockedCell(int x, int z, bool blocked);
    bool IsWalkable(int x, int z) const;

    std::vector<Vector3> FindPath(
        const Vector3& start,
        const Vector3& goal
    ) const;

private:
    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> blocked{};
};
