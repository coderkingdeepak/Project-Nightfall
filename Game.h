#pragma once

#include "InputSystem.h"
#include "MovementSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "HealthSystem.h"
#include "CameraSystem.h"
#include "RaycastSystem.h"
#include "World.h"
#include "ObjectiveSystem.h"
#include "PathfindingSystem.h"

class Game
{
public:
   
    void Initialize();
    void Run();
    void Shutdown();

private:
   
    InputSystem inputSystem;
    MovementSystem movementSystem;
    HealthSystem healthSystem;
    CameraSystem cameraSystem;
    RaycastSystem raycastSystem;

   
    InputState currentInput;

  
    World world;
    ObjectiveSystem objectiveSystem;
    PathfindingSystem pathfindingSystem;
    
    void ProcessInput();
    void Update(float deltaTime);
    void Render();

    bool isRunning = false;
    float attackRange = 2.0f;
    int playerAttackDamage = 25;
    int enemyAttackDamage = 10;
    float enemyAttackCooldown = 1.0f;
    float enemyAttackTimer = 0.0f;
};