#pragma once
#include "Sprite.h"

class Background
{
public:
    Background(Sprite* sprite, float scrollRatio, Vec2 scrollVel);

    Sprite* m_sprite;
    float m_fScrollRatio;
    Vec2 m_vec2ScrollVel;
};