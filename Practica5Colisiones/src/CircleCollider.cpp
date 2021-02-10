#include "CircleCollider.h"

#include <cstdio>


CircleCollider::CircleCollider(const Vec2& circlePos, float circleRadius)
{
    position = circlePos;
    radius = circleRadius;
    //colType = 1;
}

bool CircleCollider::collides(const Collider& other) const
{
    bool collision = other.collides(position, radius);
    return collision; 
}

bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const
{
    return checkCircleCircle(position, radius, circlePos, circleRadius);
}

bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
    return checkCircleRect(position, radius, rectPos, rectSize);
}

bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    return checkCirclePixels(position, radius, pixelsPos, pixelsSize, pixels);
}
