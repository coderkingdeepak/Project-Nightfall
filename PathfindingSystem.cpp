#include "PathfindingSystem.h"

#include <algorithm>
#include <cmath>
#include <limits>

PathfindingSystem::PathfindingSystem() = default;

void PathfindingSystem::SetBlockedCell(
    int x, int z, bool isBlocked)
{
    if (x < 0 || x >= GRID_SIZE ||
        z < 0 || z >= GRID_SIZE)
        return;

    blocked[x][z] = isBlocked;
}

bool PathfindingSystem::IsWalkable(int x, int z) const
{
    return x >= 0 && x < GRID_SIZE &&
        z >= 0 && z < GRID_SIZE &&
        !blocked[x][z];
}

std::vector<Vector3> PathfindingSystem::FindPath(
    const Vector3& start,
    const Vector3& goal) const
{
    const int sx = static_cast<int>(std::round(start.x));
    const int sz = static_cast<int>(std::round(start.z));
    const int gx = static_cast<int>(std::round(goal.x));
    const int gz = static_cast<int>(std::round(goal.z));

    if (!IsWalkable(sx, sz) || !IsWalkable(gx, gz))
        return {};

    struct Node
    {
        int x, z;
        int g, h;
        int parent;
    };

    constexpr int INF = std::numeric_limits<int>::max();

    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> gScore;
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> parent;
    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> closed{};

    for (int x = 0; x < GRID_SIZE; ++x)
    {
        gScore[x].fill(INF);
        parent[x].fill(-1);
    }

    auto heuristic = [&](int x, int z)
        {
            return std::abs(gx - x) + std::abs(gz - z);
        };

    std::vector<Node> nodes;
    std::vector<int> open;

    nodes.push_back({ sx, sz, 0, heuristic(sx, sz), -1 });
    open.push_back(0);
    gScore[sx][sz] = 0;

    const int dx[] = { 1, -1, 0, 0 };
    const int dz[] = { 0, 0, 1, -1 };

    int goalNode = -1;

    while (!open.empty())
    {
        auto best = std::min_element(
            open.begin(), open.end(),
            [&](int a, int b)
            {
                return nodes[a].g + nodes[a].h <
                    nodes[b].g + nodes[b].h;
            });

        int currentIndex = *best;
        open.erase(best);

        const Node current = nodes[currentIndex];

        if (closed[current.x][current.z])
            continue;

        closed[current.x][current.z] = true;

        if (current.x == gx && current.z == gz)
        {
            goalNode = currentIndex;
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nx = current.x + dx[i];
            int nz = current.z + dz[i];

            if (!IsWalkable(nx, nz) || closed[nx][nz])
                continue;

            int tentativeG = current.g + 1;

            if (tentativeG >= gScore[nx][nz])
                continue;

            gScore[nx][nz] = tentativeG;
            parent[nx][nz] = currentIndex;

            nodes.push_back({
                nx, nz, tentativeG,
                heuristic(nx, nz), currentIndex
                });

            open.push_back(
                static_cast<int>(nodes.size()) - 1
            );
        }
    }

    if (goalNode == -1)
        return {};

    std::vector<Vector3> path;

    for (int index = goalNode;
        index != -1;
        index = nodes[index].parent)
    {
        const Node& node = nodes[index];

        if (node.x == sx && node.z == sz)
            break;

        path.emplace_back(
            static_cast<float>(node.x),
            start.y,
            static_cast<float>(node.z)
        );
    }

    std::reverse(path.begin(), path.end());
    return path;
}