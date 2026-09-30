#include "Entity.h"

void Entity::SetPosition(const Vector3& newPosition)
{
    position = newPosition;
}

Vector3 Entity::GetPosition() const
{
    return position;
}