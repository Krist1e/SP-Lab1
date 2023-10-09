#include "Borders.h"

using Windows::Foundation::Numerics::float2;

Borders::Borders()
{
    borders = D2D1::RectF(0, 0, 0, 0);
    collisions.reserve(2);
}

const std::vector<CollisionInfo>& Borders::CheckCollision(const D2D1_RECT_F& rect)
{
    collisions.clear();

    if (rect.left < borders.left)
        collisions.emplace_back(CollisionInfo{float2(1, 0), borders.left - rect.left});

    if (rect.right > borders.right)
        collisions.emplace_back(CollisionInfo{float2(-1, 0), rect.right - borders.right});

    if (rect.top < borders.top)
        collisions.emplace_back(CollisionInfo{float2(0, 1), borders.top - rect.top});

    if (rect.bottom > borders.bottom)
        collisions.emplace_back(CollisionInfo{float2(0, -1), rect.bottom - borders.bottom});

    return collisions;
}

void Borders::SetSize(const UINT width, const UINT height)
{
    borders = D2D1::RectF(0, 0, width, height);
}
