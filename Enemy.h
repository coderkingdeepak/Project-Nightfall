#pragma once

#include "Entity.h"
#include <vector>
enum class EnemyState
{
    Patrol,
    Alert,
    Chase
};
class Enemy : public Entity
{
public:
    Enemy();

    void Update(float deltaTime) override;
    bool IsAlive() const override;

    void SetHealth(int newHealth);
    int GetHealth() const;
    void TakeDamage(int damage);
    void DetectPlayer(
        const Vector3& playerPosition,
        bool playerCrouching,
        bool hasLineOfSight
    );
    bool IsPlayerDetected() const;
    EnemyState GetState() const;
    void SetTargetPosition(const Vector3& target);

    Vector3 targetPosition;
    float chaseSpeed = 3.5f;
    void SetPath(const std::vector<Vector3>& newPath);
private:
    int health;
    int maxHealth;
    std::vector<Vector3> patrolPoints;
    std::size_t currentPatrolIndex = 1;
    float patrolSpeed = 2.0f;
    float detectionRange = 8.0f;
    bool playerDetected = false;
    EnemyState state = EnemyState::Patrol;
    std::vector<Vector3> currentPath;
    std::size_t currentPathIndex = 0;
};