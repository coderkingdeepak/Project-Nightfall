#pragma once

#include "Player.h"
#include "Enemy.h"

class HealthSystem
{
public:
    void Update(Player& player, Enemy& enemy, float deltaTime);

    void DamagePlayer(Player& player, int damage);
    void DamageEnemy(Enemy& enemy, int damage);
};