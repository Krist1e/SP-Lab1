#include "Input.h"
#include <Windowsx.h>

void Input::OnKeyDown(const WPARAM key)
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

void Input::OnKeyUp(const WPARAM key)
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

void Input::OnMouseDown(WPARAM wParam, LPARAM lParam)
{
    if (wParam & MK_LBUTTON)
        isMouseLeftPressed = true;

    mouseX = GET_X_LPARAM(lParam);
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::OnMouseUp(WPARAM wParam, LPARAM lParam)
{
    if (wParam & MK_LBUTTON)
        isMouseLeftPressed = false;

    mouseX = GET_X_LPARAM(lParam);
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::OnMouseMove(const LPARAM lParam)
{
    mouseX = GET_X_LPARAM(lParam);
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::OnMouseWheel(const WPARAM wParam)
{
    const float delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
    if (wParam & MK_SHIFT)
        mouseWheelDeltaWithShift += delta;
    else
        mouseWheelDelta += delta;
}

bool Input::IsMouseOver(const D2D1_RECT_F rect) const
{
    if (mouseX < rect.left || mouseX > rect.right)
        return false;
    return mouseY >= rect.top && mouseY <= rect.bottom;
}

float2 Input::GetKeyboardMovement() const
{
    float2 movement = {};
    if (isLeftPressed)
        movement.x -= 1.0f;
    if (isRightPressed)
        movement.x += 1.0f;
    if (isUpPressed)
        movement.y -= 1.0f;
    if (isDownPressed)
        movement.y += 1.0f;

    return movement;
}

float2 Input::GetMouseMovement(const float2 position) const
{
    const float2 mousePosition = {mouseX, mouseY};
    const float2 distance = mousePosition - position;
    float2 movement = {};

    if (length_squared(distance) > 0.0f)
        movement = normalize(distance);

    return movement;
}

float2 Input::GetMouseWheelMovement()
{
    float2 movement = {mouseWheelDeltaWithShift, mouseWheelDelta};
    if (length_squared(movement) > 0.0f)
        movement = normalize(movement);

    mouseWheelDelta = 0.0f;
    mouseWheelDeltaWithShift = 0.0f;

    return movement;
}
