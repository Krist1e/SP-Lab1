#pragma once
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "WindowsNumerics.h"

using Windows::Foundation::Numerics::float2;

class Sprite {
public:
    Sprite();
    void Update();
    void Draw();
    void Move(float2 direction);

private:
    D2D1_RECT_F rect;
};
