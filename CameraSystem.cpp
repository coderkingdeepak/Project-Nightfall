#include "CameraSystem.h"

void CameraSystem::Update(const Player& player)
{
    cameraPosition = player.GetPosition() + cameraOffset;
}

Vector3 CameraSystem::GetCameraPosition() const
{
    return cameraPosition;
}