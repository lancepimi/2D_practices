#pragma once

#include "Collider.h"
#include "Vec2.h"

class CircleCollider : public Collider
{
public:
    CircleCollider(const Vec2& circlePos, float circleRadius);

    virtual bool collides(const Collider& other) const override;
    virtual bool collides(const Vec2& circlePos, float circleRadius) const override;
    virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const override;
    virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const override;
};
