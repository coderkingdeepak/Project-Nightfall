#include "MovementSystem.h"

void MovementSystem::Update(
    Player& player,
    const InputState& input,
    float deltaTime)
{
    Vector3 direction(0.0f, 0.0f, 0.0f);

    if (input.moveForward)
        direction.z += 1.0f;

    if (input.moveBackward)
        direction.z -= 1.0f;

    if (input.moveRight)
        direction.x += 1.0f;

    if (input.moveLeft)
        direction.x -= 1.0f;

    if (direction.Magnitude() > 0.0f)
    {
        direction = direction.Normalize();

        Vector3 movement = direction * (movementSpeed * deltaTime);

        player.SetPosition(player.GetPosition() + movement);
    }
}