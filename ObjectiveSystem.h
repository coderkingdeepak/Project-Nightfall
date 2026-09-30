#pragma once

#include "Player.h"
#include "World.h"

class ObjectiveSystem
{
public:
    void Update(const Player& player, World& world);

    bool IsDataRetrieved() const;
    bool IsExtractionReached() const;
    void TryInteract(const Player& player, World& world);
private:
    bool dataRetrieved = false;
    bool extractionReached = false;

    Vector3 dataLocation = Vector3(10.0f, 0.0f, 10.0f);
    Vector3 extractionLocation = Vector3(20.0f, 0.0f, 20.0f);

    float interactionRange = 1.5f;
    float extractionRange = 2.0f;
};
