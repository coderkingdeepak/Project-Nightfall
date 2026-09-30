#pragma once

#include "Vector3.h"

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0;
    virtual bool IsAlive() const = 0;

    void SetPosition(const Vector3& newPosition);
    Vector3 GetPosition() const;

protected:
    Vector3 position;
};
