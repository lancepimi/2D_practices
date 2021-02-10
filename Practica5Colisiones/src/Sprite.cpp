#include "Sprite.h"
#include <algorithm>
#include <iostream>

#include "PixelsCollider.h"


Sprite::Sprite(const ltex_t* _tex, CollisionType type, Vec2 pos, const char* name, float _hFrames, float _vFrames)
{
	texture = _tex;
	vecPosition = pos;
	Collision = type;
	textureName = name;

	setColor(1, 1, 1, 1);

	setCollisionType(type);

	scale = Vec2(1, 1);

	////asignar collider calculando posición y
	//if (type == COLLISION_CIRCLE)
	//{	
	//	const float radius = texture->width * 0.5;
	//	m_collider = new CircleCollider(pos, radius);
	//}
	//if (type == COLLISION_RECT)
	//{
	//	const Vec2 size = Vec2(texture->width, texture->height);
	//	m_collider = new RectCollider(pos, size);
	//}
	//if (type == COLLISION_PIXELS)
	//{
	//	//const Vec2 position(Vec2(getPosition().GetX(), getPosition().GetY()));
	//	const Vec2 rectSize = Vec2(texture->width, texture->height);
	//	m_collider = new RectCollider(pos, rectSize);

	//	unsigned char* pixels = new unsigned char[texture->width * texture->height * 4];
	//	ltex_getpixels(texture, pixels);

	//	if (pixels)
	//	{
	//		printf("jhsfdjk");
	//		m_collider = new PixelsCollider(pos, Vec2(texture->width, texture->height), (uint8_t*)pixels);
	//	}
	//}

    setColPosition(vecPosition);
}

const ltex_t* Sprite::getTexture() const
{
	return texture;
}

void Sprite::setTexture(const ltex_t* _texture, int hframes, int vframes)
{
	texture = _texture;
}

lblend_t Sprite::getBlend() const
{
	return mode;
}

void Sprite::setBlend(lblend_t _mode)
{
	mode = _mode;
}

const char* Sprite::GetTextureName() const
{
	return textureName;
}

float Sprite::getRed() const
{
	return fRed;
}

float Sprite::getGreen() const
{
	return fGreen;
}

float Sprite::getBlue() const
{
	return fBlue;
}

float Sprite::getAlpha() const
{
	return fAlpha;
}

void Sprite::setColor(float _r, float _g, float _b, float _a)
{
	fRed = _r;
	fGreen = _g;
	fBlue = _b;
	fAlpha = _a;
}

const Vec2& Sprite::getPosition() const
{
	return vecPosition;
}

void Sprite::setPosition(const Vec2& pos)
{
	vecPosition = pos;
}

void Sprite::setCollisionType(CollisionType type)
{
	Collision = type;
	//asignar collider calculando posición y
	if (type == COLLISION_CIRCLE)
    {
		const Vec2 position(Vec2(getPosition().GetX(), getPosition().GetY()));
        const float radius = texture->width * 0.5 * scale.GetX();
        m_collider = new CircleCollider(position, radius);
    }
    if (type == COLLISION_RECT)
    {
		const Vec2 position(Vec2(getPosition().GetX(), getPosition().GetY()));
        const Vec2 rectSize = Vec2(texture->width * scale.GetX(), texture->height * scale.GetY());
        m_collider = new RectCollider(position, rectSize);
    }
    if (type == COLLISION_PIXELS)
    {
		const Vec2 position(Vec2(getPosition().GetX(), getPosition().GetY()));
        const Vec2 rectSize = Vec2(texture->width, texture->height);
        m_collider = new RectCollider(position, rectSize);

		unsigned char* pixels = new unsigned char[texture->width * texture->height * 4];
		ltex_getpixels(texture, pixels);

		if (pixels)
		{
			m_collider = new PixelsCollider(vecPosition, Vec2(texture->width, texture->height), (uint8_t*)pixels);
		}
    }
}

CollisionType Sprite::getCollisionType() const
{
	return Collision;
}

const Vec2& Sprite::getColPosition() const
{
	return colPosition;
}

void Sprite::setColPosition(const Vec2& pos)
{
	colPosition = pos;
}

const Collider* Sprite::getCollider() const
{
	return m_collider;
}

double Sprite::clamp(double x, double upper, double lower)
{
	return std::max(lower, std::min(x, upper));
}

void Sprite::update(float* deltaTime, float elapsed_seconds, double* dXMouse, double* dYMouse)
{
	if (*dXMouse != 0 && *dYMouse != 0)
	{
        vecMousePosition = Vec2(*dXMouse, *dYMouse);

	    setPosition(Vec2(vecMousePosition));
	}

	m_collider->setCollisionPos(vecPosition);
	setColPosition(vecPosition);
}

void Sprite::draw() const
{
	lgfx_setblend(mode);
	lgfx_setcolor(fRed, fGreen, fBlue, fAlpha);
	ltex_drawrotsized(texture, vecPosition.GetX(), vecPosition.GetY(), 0, 0.5f, 0.5f,	(texture->width) * scale.GetX(), (texture->height) * scale.GetY(), 0, 0, 1, 1);
}

void Sprite::setScale(const Vec2& _scale)
{
	scale = _scale;
	setCollisionType(getCollisionType());
}
