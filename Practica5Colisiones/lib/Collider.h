#pragma once

#include <cstdint>
#include "Vec2.h"


class Collider
{
protected:
    Vec2 position;
    float radius;
    Vec2 rectColtSize;
    int colType;

public:

    virtual bool collides(const Collider& other) const = 0;
    virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
    virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
    virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;

    bool checkCircleCircle(const Vec2& pos1, float radius1,
        const Vec2& pos2, float radius2)const;
    bool checkCircleRect(const Vec2& circlePos, float circleRadius,
        const Vec2& rectPos, const Vec2& rectSize) const;
    bool checkCirclePixels(const Vec2& circlePos, float circleRadius,
        const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
    bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1,
        const Vec2& rectPos2, const Vec2& rectSize2) const;
    bool checkRectPixels(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize) const;
    bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1,
        const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2) const;

    Vec2 getCollisionPos() const;
    void setCollisionPos(Vec2 pos);

    Vec2 getRectColSize() const;
    void setRectColSize(Vec2 size);

    float getRadius() const;
    void setRadius(float rad);

    int getColType() const;
    void setColType(int type);

};
