#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
void Game::Initialize()
{
    world.Initialize();
    world.StartMission();
   
    for (int z = 4; z <= 14; z++)
    {
        pathfindingSystem.SetBlockedCell(8, z, true);
    }
    isRunning = true;
}
void Game::Run()
{
    int renderCounter = 0;

    while (isRunning)
    {
        ProcessInput();
        Update(0.016f);

        renderCounter++;

        if (renderCounter >= 30)
        {
            Render();
            renderCounter = 0;
        }

       
        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }
}
void Game::ProcessInput()
{
    inputSystem.Update();
    currentInput = inputSystem.GetInput();
    if (currentInput.crouch)
    {
        Player* player = world.GetPlayer();

        if (player != nullptr)
            player->ToggleCrouch();
    }
    if (currentInput.exit)
    {
        Shutdown();
    }
}
void Game::Update(float deltaTime)
{
    if (deltaTime <= 0.0f)
        return;

    world.Update(deltaTime);

    Player* player = world.GetPlayer();
    Enemy* enemy = world.GetEnemy();

    if (player == nullptr || enemy == nullptr)
        return;

    if (world.GetMissionState() != MissionState::Active)
        return;

    
    movementSystem.Update(*player, currentInput, deltaTime);

   
    cameraSystem.Update(*player);

  
    raycastSystem.Update(*player, world, pathfindingSystem);

    enemy->DetectPlayer(
        player->GetPosition(),
        player->IsCrouching(),
        raycastSystem.HasLineOfSight()
    );

    enemy->SetTargetPosition(player->GetPosition());

  
    if (enemy->GetState() != EnemyState::Patrol &&
        enemy->IsAlive())
    {
        std::vector<Vector3> path =
            pathfindingSystem.FindPath(
                enemy->GetPosition(),
                player->GetPosition()
            );

        enemy->SetPath(path);
    }

   
    float distance =
        (enemy->GetPosition() - player->GetPosition()).Magnitude();

    if (currentInput.attack &&
        enemy->IsAlive() &&
        distance <= attackRange)
    {
        healthSystem.DamageEnemy(
            *enemy,
            playerAttackDamage
        );

        std::cout << "\nPlayer attacked enemy!\n";
        std::cout << "Enemy health: "
            << enemy->GetHealth() << '\n';
    }

    // 7. Enemy attack when close enough
    if (enemy->IsAlive() &&
        player->IsAlive() &&
        distance <= attackRange &&
        enemy->GetState() == EnemyState::Chase)
    {
        enemyAttackTimer += deltaTime;

        if (enemyAttackTimer >= enemyAttackCooldown)
        {
            healthSystem.DamagePlayer(
                *player,
                enemyAttackDamage
            );

            enemyAttackTimer = 0.0f;

            std::cout << "\nEnemy attacked player!\n";
            std::cout << "Player health: "
                << player->GetHealth() << '\n';
        }
    }
    else
    {
        enemyAttackTimer = 0.0f;
    }

    // 8. Player interaction
    if (currentInput.interact)
    {
        objectiveSystem.TryInteract(*player, world);
    }

    // 9. Mission objectives
    objectiveSystem.Update(*player, world);

    // 10. Mission failure
    if (!player->IsAlive())
    {
        world.FailMission();
        std::cout << "\nMISSION FAILED - PLAYER DEFEATED!\n";
        Shutdown();
        return;
    }

    // 11. Mission completion
    if (world.GetMissionState() == MissionState::Completed)
    {
        std::cout << "\nMISSION COMPLETED!\n";
        Shutdown();
    }
}


void Game::Render()
{
    Player* player = world.GetPlayer();
    Enemy* enemy = world.GetEnemy();

    if (player == nullptr || enemy == nullptr)
        return;

    std::cout << "\n========== NIGHTFALL ==========\n";

    std::cout << "Player position: "
        << player->GetPosition().x << ", "
        << player->GetPosition().y << ", "
        << player->GetPosition().z << '\n';

    std::cout << "Player health: "
        << player->GetHealth() << '\n';

    std::cout << "Player stance: "
        << (player->IsCrouching() ? "CROUCHING" : "STANDING")
        << '\n';

    std::cout << "Enemy position: "
        << enemy->GetPosition().x << ", "
        << enemy->GetPosition().y << ", "
        << enemy->GetPosition().z << '\n';

    std::cout << "Enemy health: "
        << enemy->GetHealth() << '\n';

    const char* stateName = "PATROL";

    switch (enemy->GetState())
    {
    case EnemyState::Patrol:
        stateName = "PATROL";
        break;
    case EnemyState::Alert:
        stateName = "ALERT";
        break;
    case EnemyState::Chase:
        stateName = "CHASE";
        break;
    }

    std::cout << "Enemy state: " << stateName << '\n';
    std::cout << "Line of sight: "
        << (raycastSystem.HasLineOfSight() ? "CLEAR" : "BLOCKED")
        << '\n';

    std::cout << "Data retrieved: "
        << (objectiveSystem.IsDataRetrieved() ? "YES" : "NO")
        << '\n';

    std::cout << "Extraction reached: "
        << (objectiveSystem.IsExtractionReached() ? "YES" : "NO")
        << '\n';

    std::cout << "Controls: WASD move | C crouch | F attack | "
        "E interact | ESC quit\n";

    std::cout << "================================\n";
}
void Game::Shutdown()
{
    isRunning = false;
}