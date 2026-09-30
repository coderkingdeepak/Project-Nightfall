#pragma once

#include "Player.h"
#include "Vector3.h"

class CameraSystem
{
public:
    void Update(const Player& player);

    Vector3 GetCameraPosition() const;

private:
    Vector3 cameraPosition;
    Vector3 cameraOffset = Vector3(0.0f, 5.0f, -8.0f);
};