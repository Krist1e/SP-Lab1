#pragma once
#include <windows.h>
#include <d2d1.h>
#include <WindowsNumerics.h>

using Windows::Foundation::Numerics::float2;

class Input
{
public:
    void OnKeyDown(WPARAM key);
    void OnKeyUp(WPARAM key);

    void OnMouseDown(WPARAM wParam, LPARAM lParam);
    void OnMouseUp(WPARAM wParam, LPARAM lParam);
    void OnMouseMove(LPARAM lParam);

    void OnMouseWheel(WPARAM wParam);

    bool IsMouseOver(D2D1_RECT_F rect) const;

    float2 GetKeyboardMovement() const;
    float2 GetMouseMovement(float2 position) const;
    float2 GetMouseWheelMovement();

private:
    bool isLeftPressed = false;
    bool isRightPressed = false;
    bool isUpPressed = false;
    bool isDownPressed = false;

    bool isMouseLeftPressed = false;
    float mouseX = 0.0f;
    float mouseY = 0.0f;

    float mouseWheelDelta = 0.0f;
    float mouseWheelDeltaWithShift = 0.0f;
};
