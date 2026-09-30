#include "ObjectiveSystem.h"

void ObjectiveSystem::Update(const Player& player, World& world)
{
    if (world.GetMissionState() != MissionState::Active)
        return;

    if (!dataRetrieved)
        return;

    float distance =
        (player.GetPosition() - extractionLocation).Magnitude();

    if (distance <= extractionRange)
    {
        extractionReached = true;
        world.CompleteMission();
    }
}

bool ObjectiveSystem::IsDataRetrieved() const
{
    return dataRetrieved;
}

bool ObjectiveSystem::IsExtractionReached() const
{
    return extractionReached;
}
void ObjectiveSystem::TryInteract(const Player& player, World& world)
{
    if (world.GetMissionState() != MissionState::Active)
        return;

    if (dataRetrieved)
        return;

    float distance =
        (player.GetPosition() - dataLocation).Magnitude();

    if (distance <= interactionRange)
    {
        dataRetrieved = true;
    }
}