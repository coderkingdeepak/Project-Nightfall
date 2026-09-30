#include "RaycastSystem.h"
#include <cmath>

void RaycastSystem::Update(
    const Player& player,
    const World& world,
    const PathfindingSystem& pathfinding)
{
    lineOfSight = false;

    const Enemy* enemy = world.GetEnemy();

    if (enemy == nullptr || !enemy->IsAlive())
        return;

    Vector3 start = player.GetPosition();
    Vector3 end = enemy->GetPosition();

    if ((end - start).Magnitude() > range)
        return;

    int x0 = static_cast<int>(std::round(start.x));
    int z0 = static_cast<int>(std::round(start.z));
    int x1 = static_cast<int>(std::round(end.x));
    int z1 = static_cast<int>(std::round(end.z));

    int dx = std::abs(x1 - x0);
    int dz = std::abs(z1 - z0);

    int sx = (x0 < x1) ? 1 : -1;
    int sz = (z0 < z1) ? 1 : -1;
    int error = dx - dz;

    int x = x0;
    int z = z0;

    while (true)
    {
        if (!pathfinding.IsWalkable(x, z))
            return;

        if (x == x1 && z == z1)
            break;

        int doubledError = 2 * error;

        if (doubledError > -dz)
        {
            error -= dz;
            x += sx;
        }

        if (doubledError < dx)
        {
            error += dx;
            z += sz;
        }
    }

    lineOfSight = true;
}

bool RaycastSystem::HasLineOfSight() const
{
    return lineOfSight;
}