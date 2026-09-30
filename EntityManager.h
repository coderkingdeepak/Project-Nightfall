#pragma once

#include "Entity.h"
#include <memory>
#include <vector>

class EntityManager
{
public:
    void AddEntity(std::unique_ptr<Entity> entity);

    void UpdateAll(float deltaTime);
    void RemoveInactive();

    size_t GetEntityCount() const;

private:
    std::vector<std::unique_ptr<Entity>> entities;
};
