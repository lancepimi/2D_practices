
#include "PixelsCollider.h"


PixelsCollider::PixelsCollider(const Vec2& pixelsPos, const Vec2& pixelsSize, uint8_t* pixels)
{
	position = pixelsPos;
	m_pixelsSize = pixelsSize;
	m_pixels = pixels;
}

PixelsCollider::~PixelsCollider()
{
	delete[] m_pixels;
}

bool PixelsCollider::collides(const Collider& other) const
{
	return other.collides(position, m_pixelsSize, m_pixels);
}

bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return checkCirclePixels(circlePos, circleRadius, position, m_pixelsSize, m_pixels);
}

bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	return checkRectPixels(position, m_pixelsSize, m_pixels, rectPos, rectSize);
}

bool PixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return checkPixelsPixels(pixelsPos, pixelsSize, pixels, position, m_pixelsSize, m_pixels);
}

Vec2 PixelsCollider::getPixelsSize() const
{
	return m_pixelsSize;
}

void PixelsCollider::setPixelsSize(const Vec2 pixelsSize)
{
	m_pixelsSize = pixelsSize;
}

uint8_t* PixelsCollider::getPixels() const
{
	return m_pixels;
}

void PixelsCollider::setPixels(uint8_t* pixels)
{
	m_pixels = pixels;
}
