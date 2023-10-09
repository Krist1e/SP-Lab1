#pragma once
#include <comdef.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "KeyboardInput.h"
#include "WindowsNumerics.h"

_COM_SMARTPTR_TYPEDEF(ID2D1Bitmap, __uuidof(ID2D1Bitmap));

using Windows::Foundation::Numerics::float2;

class Sprite {
public:
    explicit Sprite(KeyboardInput* keyboard_input);
    void Update(float deltaTime);
    void Draw(ID2D1RenderTarget& renderTarget) const;

    void SetBitmap(const ID2D1BitmapPtr& bitmap);
private:
    KeyboardInput* keyboardInput;
    ID2D1BitmapPtr bitmap;

    D2D1_SIZE_F size;
    D2D1_RECT_F rect;
    float2 velocity;
    float2 position;

    float2 HandleInput() const;
};
