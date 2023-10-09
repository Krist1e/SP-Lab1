#pragma once
#include <d2d1.h>
#include <vector>

#include "CollisionInfo.h"

class Borders
{
public:
    Borders();
    const std::vector<CollisionInfo>& CheckCollision(const D2D1_RECT_F& rect);
    void SetSize(const UINT width, const UINT height);

private:
    D2D1_RECT_F borders;
    std::vector<CollisionInfo> collisions;
};
