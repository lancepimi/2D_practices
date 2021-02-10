#pragma once

#include "Collider.h"
#include "Vec2.h"

class PixelsCollider : public Collider
{
public:
    PixelsCollider(const Vec2& pixelsPos, const Vec2& pixelsSize, uint8_t* pixels);
    ~PixelsCollider();

    virtual bool collides(const Collider& other) const override;
    virtual bool collides(const Vec2& circlePos, float circleRadius) const override;
    virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const override;
    virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const override;

    Vec2 getPixelsSize() const;
    void setPixelsSize(const Vec2 pixelsSize);

    uint8_t* getPixels() const;
    void setPixels(uint8_t* pixels);

private:
    Vec2 m_pixelsSize;
    uint8_t* m_pixels;
};