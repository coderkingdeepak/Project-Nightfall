#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player();

    void Update(float deltaTime) override;
    bool IsAlive() const override;

    void TakeDamage(int damage);
    int GetHealth() const;
    void ToggleCrouch();
    bool IsCrouching() const;
private:
    int health;
    int maxHealth;
    bool isCrouching = false;
};