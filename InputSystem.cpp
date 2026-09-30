#include "InputSystem.h"
#include <conio.h>

void InputSystem::Update()
{
    input = InputState{};

    if (_kbhit())
    {
        char key = _getch();

        switch (key)
        {
        case 'w':
        case 'W':
            input.moveForward = true;
            break;

        case 's':
        case 'S':
            input.moveBackward = true;
            break;

        case 'a':
        case 'A':
            input.moveLeft = true;
            break;
        case 'c':
        case 'C':
            input.crouch = true;
            break;
        case 'd':
        case 'D':
            input.moveRight = true;
            break;

        case 'f':
        case 'F':
            input.attack = true;
            break;

        case 'e':
        case 'E':
            input.interact = true;
            break;

        case 27:
            input.exit = true;
            break;
        }
    }
}

InputState InputSystem::GetInput() const
{
    return input;
}