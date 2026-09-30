#include "Enemy.h"
#include <algorithm>

Enemy::Enemy() : health(100), maxHealth(100)
{
    position = Vector3(5.0f, 0.0f, 5.0f);

    patrolPoints = {
        Vector3(5.0f, 0.0f, 5.0f),
        Vector3(15.0f, 0.0f, 5.0f),
        Vector3(15.0f, 0.0f, 15.0f),
        Vector3(5.0f, 0.0f, 15.0f)
    };
}

void Enemy::Update(float deltaTime)
{
    if (!IsAlive())
        return;

    if (deltaTime <= 0.0f)
        return;

    if (state == EnemyState::Alert)
        state = EnemyState::Chase;

    if (state == EnemyState::Chase)
    {
        if (currentPathIndex >= currentPath.size())
            return;

        Vector3 target = currentPath[currentPathIndex];
        Vector3 direction = target - position;
        float distance = direction.Magnitude();
        float movementStep = chaseSpeed * deltaTime;

        if (distance <= movementStep)
        {
            position = target;
            currentPathIndex++;
        }
        else
        {
            position = position +
                direction.Normalize() * movementStep;
        }

        return;
    }

    if (patrolPoints.empty())
        return;

    Vector3 target = patrolPoints[currentPatrolIndex];
    Vector3 direction = target - position;
    float distance = direction.Magnitude();
    float movementStep = patrolSpeed * deltaTime;

    if (distance <= movementStep)
    {
        position = target;
        currentPatrolIndex =
            (currentPatrolIndex + 1) % patrolPoints.size();
    }
    else
    {
        position = position +
            direction.Normalize() * movementStep;
    }
}

bool Enemy::IsAlive() const
{
    return health > 0;
}

void Enemy::SetHealth(int newHealth)
{
    health = std::clamp(newHealth, 0, maxHealth);
}

int Enemy::GetHealth() const
{
    return health;
}

void Enemy::TakeDamage(int damage)
{
    if (damage <= 0)
        return;

    SetHealth(health - damage);
}
void Enemy::DetectPlayer(
    const Vector3& playerPosition,
    bool playerCrouching,
    bool hasLineOfSight)
{
    if (!IsAlive())
    {
        playerDetected = false;
        return;
    }

    float distance = (position - playerPosition).Magnitude();

    float effectiveRange = playerCrouching
        ? detectionRange * 0.5f
        : detectionRange;

    playerDetected =
        hasLineOfSight && distance <= effectiveRange;

    if (playerDetected)
        state = EnemyState::Alert;
}
bool Enemy::IsPlayerDetected() const
{
    return playerDetected;
}

EnemyState Enemy::GetState() const
{
    return state;
}

void Enemy::SetTargetPosition(const Vector3& target)
{
    targetPosition = target;
}
void Enemy::SetPath(const std::vector<Vector3>& newPath)
{
    currentPath = newPath;
    currentPathIndex = 0;
}