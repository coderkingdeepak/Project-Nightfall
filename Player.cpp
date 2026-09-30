#include "Player.h"
#include <algorithm>

Player::Player()
    : health(100), maxHealth(100)
{
    position = Vector3(0.0f, 0.0f, 0.0f);
}

void Player::Update(float deltaTime)
{
 
}

bool Player::IsAlive() const
{
    return health > 0;
}

void Player::TakeDamage(int damage)
{
    if (damage <= 0)
        return;

    health = std::max(0, health - damage);
}

int Player::GetHealth() const
{
    return health;
}
void Player::ToggleCrouch()
{
    isCrouching = !isCrouching;
}

bool Player::IsCrouching() const
{
    return isCrouching;
}