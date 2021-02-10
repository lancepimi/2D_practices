#include "RectCollider.h"
#include <cstdio>

RectCollider::RectCollider(const Vec2& rectPos, const Vec2& rectSize)
{
    position = rectPos;
    rectColtSize = rectSize;
    //colType = 2;
}

bool RectCollider::collides(const Collider& other) const
{
    bool collision = other.collides(position, rectColtSize);
    return collision;
}

bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const
{
    return checkCircleRect(circlePos, circleRadius, position,rectColtSize);
}

bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
    return checkRectRect(position, rectColtSize, rectPos, rectSize);
}

bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    return checkRectPixels( pixelsPos, pixelsSize, pixels, position, rectColtSize );
}
