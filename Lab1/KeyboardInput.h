#pragma once
#include <windows.h>

class KeyboardInput
{
public:
    void OnKeyDown(WPARAM key);
    void OnKeyUp(WPARAM key);

    bool IsLeftPressed() const { return isLeftPressed; }
    bool IsRightPressed() const { return isRightPressed; }
    bool IsUpPressed() const { return isUpPressed; }
    bool IsDownPressed() const { return isDownPressed; }
private:
    bool isLeftPressed = false;
    bool isRightPressed = false;
    bool isUpPressed = false;
    bool isDownPressed = false;
};
