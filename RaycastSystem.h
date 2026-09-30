#pragma once

#include "Player.h"
#include "World.h"
#include "PathfindingSystem.h"

class RaycastSystem
{
public:
    void Update(
        const Player& player,
        const World& world,
        const PathfindingSystem& pathfinding
    );

    bool HasLineOfSight() const;

private:
    bool lineOfSight = false;
    float range = 10.0f;
};