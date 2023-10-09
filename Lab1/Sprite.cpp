#include "Sprite.h"

#include "BitmapLoader.h"

Sprite::Sprite(Input* input, Borders* borders)
{
    this->input = input;
    this->borders = borders;
    rect = D2D1::RectF(0, 0, 0, 0);
    size = D2D1::SizeF(0, 0);
    acceleration = float2::zero();
    velocity = float2::zero();
    position = float2::zero();
}


float2 Sprite::GetInputDirection() const
{
    float2 direction = {};
    direction += input->GetKeyboardMovement();
    direction += input->GetMouseWheelMovement();
    if (isSelected)
        direction += input->GetMouseMovement(position);

    if (length_squared(direction) > 0.0f)
        direction = normalize(direction);

    return direction;
}

void Sprite::UpdateRect()
{
    rect = D2D1::RectF(position.x - size.width / 2, position.y - size.height / 2, position.x + size.width / 2,
                       position.y + size.height / 2);
}

void Sprite::HandleCollision()
{
    const auto& collisions = borders->CheckCollision(rect);
    for (const auto& collision : collisions)
    {
        position += collision.Normal * collision.Depth;
        acceleration -= 2 * dot(acceleration, collision.Normal) * collision.Normal;
    }
}

void Sprite::HandleInput()
{
    const float2 direction = GetInputDirection();
    acceleration += direction * speed;
}

void Sprite::Update(const float deltaTime)
{
    HandleCollision();
    HandleInput();
    velocity = acceleration * deltaTime;
    position += velocity * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;
    UpdateRect();

    acceleration -= acceleration * (deltaTime / timeToStop);
    velocity = float2::zero();
}

void Sprite::Draw(ID2D1RenderTarget& renderTarget) const
{
    if (bitmap == nullptr)
        return;

    renderTarget.DrawBitmap(bitmap, rect);
}

void Sprite::SetBitmap(const ID2D1BitmapPtr& bitmap, const float sizeMultiplier)
{
    this->bitmap = bitmap;
    size = bitmap->GetSize();
    size.width *= sizeMultiplier;
    size.height *= sizeMultiplier;
    position = float2(size.width / 2, size.height / 2);
}

void Sprite::SetSelected(const bool isSelected)
{
    this->isSelected = isSelected;
}

D2D1_RECT_F& Sprite::GetRect()
{
    return rect;
}
