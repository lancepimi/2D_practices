#include "Background.h"

Background::Background(Sprite* sprite, float scrollRatio, Vec2 scrollVel)
	: m_sprite(sprite)
	, m_fScrollRatio(scrollRatio)
	, m_vec2ScrollVel(scrollVel)
{
}