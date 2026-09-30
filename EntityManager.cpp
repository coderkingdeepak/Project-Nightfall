#include "EntityManager.h"
#include <algorithm>
#include <stdexcept>

void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
    if (!entity)
    {
        throw std::invalid_argument("Cannot add a null entity.");
    }

    entities.push_back(std::move(entity));
}

void EntityManager::UpdateAll(float deltaTime)
{
    for (const auto& entity : entities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::RemoveInactive()
{
    entities.erase(
        std::remove_if(
            entities.begin(),
            entities.end(),
            [](const std::unique_ptr<Entity>& entity)
            {
                return !entity->IsAlive();
            }),
        entities.end());
}

size_t EntityManager::GetEntityCount() const
{
    return entities.size();
}