#pragma once


#include "Player.h"
#include "InputSystem.h"

class MovementSystem
{
public:
    void Update(Player& player, const InputState& input, float deltaTime);

private:
    float movementSpeed = 5.0f;
};