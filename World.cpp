#include "World.h"
#include <memory>

void World::Initialize()
{
    auto newPlayer = std::make_unique<Player>();
    player = newPlayer.get();
    entityManager.AddEntity(std::move(newPlayer));

    auto newEnemy = std::make_unique<Enemy>();
    enemy = newEnemy.get();
    entityManager.AddEntity(std::move(newEnemy));
}
void World::Update(float deltaTime)
{
    entityManager.UpdateAll(deltaTime);
}
Player* World::GetPlayer()
{
    return player;
}

Enemy* World::GetEnemy()
{
    return enemy;
}
void World::StartMission()
{
    missionState = MissionState::Active;
}

void World::CompleteMission()
{
    missionState = MissionState::Completed;
}

void World::FailMission()
{
    missionState = MissionState::Failed;
}

MissionState World::GetMissionState() const
{
    return missionState;
}
const Enemy* World::GetEnemy() const
{
    return enemy;
}