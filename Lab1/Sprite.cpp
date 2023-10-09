#include "Sprite.h"

Sprite::Sprite(KeyboardInput* keyboard_input)
{
    keyboardInput = keyboard_input;
    rect = D2D1::RectF(0, 0, 0, 0);
    size = D2D1::SizeF(0, 0);
    velocity = float2::zero();
    position = float2::zero();
}

float2 Sprite::HandleInput() const
{
    float2 input = float2::zero();
    if (keyboardInput->IsLeftPressed())
        input.x -= 1;
    if (keyboardInput->IsRightPressed())
        input.x += 1;
    if (keyboardInput->IsUpPressed())
        input.y -= 1;
    if (keyboardInput->IsDownPressed())
        input.y += 1;

    return input;
}


void Sprite::Update(const float deltaTime)
{
    if (keyboardInput == nullptr)
        return;
    const float2 input = HandleInput();

    velocity += input * 100.0f;
    position += velocity * deltaTime;
    rect = D2D1::RectF(position.x - size.width / 2, position.y - size.height / 2, position.x + size.width / 2, position.y + size.height / 2);
    velocity = float2::zero();
}

void Sprite::Draw(ID2D1RenderTarget& renderTarget) const
{
    if (bitmap == nullptr)
        return;

    renderTarget.DrawBitmap(bitmap, rect);
}

void Sprite::SetBitmap(const ID2D1BitmapPtr& bitmap)
{
    this->bitmap = bitmap;
    size = bitmap->GetSize();
}
