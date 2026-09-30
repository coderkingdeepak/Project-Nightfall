#pragma once

struct InputState
{
    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool attack = false;
    bool interact = false;
    bool exit = false;
    bool crouch = false;
};

class InputSystem
{
public:
    void Update();
    InputState GetInput() const;

private:
    InputState input;
};