#include "KeyboardInput.h"

void KeyboardInput::OnKeyDown(WPARAM key)
{
    switch (key)
    {
    case VK_LEFT:
        isLeftPressed = true;
        break;
    case VK_RIGHT:
        isRightPressed = true;
        break;
    case VK_UP:
        isUpPressed = true;
        break;
    case VK_DOWN:
        isDownPressed = true;
        break;
    default:
        break;
    }
}

void KeyboardInput::OnKeyUp(WPARAM key)
{
    switch (key)
    {
    case VK_LEFT:
        isLeftPressed = false;
        break;
    case VK_RIGHT:
        isRightPressed = false;
        break;
    case VK_UP:
        isUpPressed = false;
        break;
    case VK_DOWN:
        isDownPressed = false;
        break;
    default:
        break;
    }
}
