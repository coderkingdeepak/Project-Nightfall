#pragma once

#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
enum class MissionState
{
    NotStarted,
    Active,
    Completed,
    Failed
};
class World
{
public:
    void Initialize();
    void Update(float deltaTime);

    Player* GetPlayer();
    Enemy* GetEnemy();
    void StartMission();
    void CompleteMission();
    void FailMission();
    MissionState GetMissionState() const;
    const Enemy* GetEnemy() const;
private:
    EntityManager entityManager;

    Player* player = nullptr;
    Enemy* enemy = nullptr;
    MissionState missionState = MissionState::NotStarted;
};
	