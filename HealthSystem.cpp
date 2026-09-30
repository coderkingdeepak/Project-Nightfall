#include "HealthSystem.h"

void HealthSystem::Update(Player& player, Enemy& enemy, float deltaTime)
{
   
}

void HealthSystem::DamagePlayer(Player& player, int damage)
{
    player.TakeDamage(damage);
}

void HealthSystem::DamageEnemy(Enemy& enemy, int damage)
{
    enemy.TakeDamage(damage);
}