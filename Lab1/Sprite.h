#pragma once
#include <comdef.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "Borders.h"
#include "Input.h"
#include "WindowsNumerics.h"

_COM_SMARTPTR_TYPEDEF(ID2D1SolidColorBrush, __uuidof(ID2D1SolidColorBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1Bitmap, __uuidof(ID2D1Bitmap));

using Windows::Foundation::Numerics::float2;

class Sprite
{
public:
    explicit Sprite(Input* input, Borders* borders);
    void Update(float deltaTime);
    void Draw(ID2D1RenderTarget& renderTarget) const;

    void SetBitmap(const ID2D1BitmapPtr& bitmap, float sizeMultiplier = 1.0f);
    void SetSelected(bool isSelected);
    D2D1_RECT_F& GetRect();

private:
    Input* input;
    Borders* borders;
    ID2D1BitmapPtr bitmap;

    D2D1_SIZE_F size;
    D2D1_RECT_F rect;
    float2 acceleration;
    float2 velocity;
    float2 position;
    static constexpr float speed = 150.0f;
    static constexpr float timeToStop = 1.2f;
    bool isSelected = false;

    float2 GetInputDirection() const;
    void UpdateRect();
    void HandleCollision();
    void HandleInput();
};
