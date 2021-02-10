#include "Collider.h"

#include <cstdio>

#include "Vec2.h"
#include <cmath>
#include <Sprite.h>

bool Collider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) const
{
    float centerDistance = pos1.distance(pos2);
    float radiusSum = radius1 + radius2;
    if (centerDistance < radiusSum)
    {
        return true;
    }
    return false;
}

bool Collider::checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize) const
{
    float closestX = Sprite::clamp(circlePos.GetX(), rectPos.GetX() + rectSize.GetX() * 0.5, rectPos.GetX() - rectSize.GetX() * 0.5);
    float closestY = Sprite::clamp(circlePos.GetY(), rectPos.GetY() + rectSize.GetY() * 0.5, rectPos.GetY() - rectSize.GetY() * 0.5);

    if( circlePos.distance(Vec2(closestX, closestY)) < circleRadius)
    {
        return true;
    }
    return false;
}

bool Collider::checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	//calculate rect collision area
	int rectCollisionWidth = pixelsSize.GetX() * 0.5 + circleRadius - std::abs(circlePos.GetX() - pixelsPos.GetX());
	int rectCollisionHeight = pixelsSize.GetY() * 0.5 + circleRadius - std::abs(circlePos.GetY() - pixelsPos.GetY());

	if (rectCollisionHeight > 0 && rectCollisionWidth > 0)
	{
		int xInit, yInit;

		if (pixelsPos.GetX() < circlePos.GetX())
		{
			//pixelsPos on the left and circle on the right
			xInit = pixelsSize.GetX() - rectCollisionWidth;
		}
		else
		{
			//circle on the left and pixelsPos on the right
			xInit = 0;
		}

		if (pixelsPos.GetY() < circlePos.GetY())
		{
			//pixelsPos on the bottom and circle on the top
			yInit = pixelsSize.GetY() - rectCollisionHeight;
		}
		else
		{
			//circle on the bottom and pixelsPos on the top
			yInit = 0;
		}

		for (int xCount = 0; xCount < rectCollisionWidth; ++xCount)
		{
			for (int yCount = 0; yCount < rectCollisionHeight; ++yCount)
			{
				//for each pixel on the collision region check alpha
				int xCountReal = xCount + xInit;
				int yCountReal = yCount + yInit;

				int pixel = (yCountReal * pixelsSize.GetX() + xCountReal) * 4; //4 color bytes
				uint8_t alpha = pixels[pixel + 3];

				if (alpha)
				{
					float pixelX = pixelsPos.GetX() + (xCountReal - (pixelsSize.GetX() / 2));
					float pixelY = pixelsPos.GetY() + (yCountReal - (pixelsSize.GetY() / 2));
					float distance = circlePos.distance(Vec2(pixelX, pixelY));
					if (distance < circleRadius)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Collider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2) const
{
    float centerPosX1 = rectPos1.GetX() - rectSize1.GetX() * 0.5f;
    float centerPosY1 = rectPos1.GetY() - rectSize1.GetY() * 0.5f;
    float centerPosX2 = rectPos2.GetX() - rectSize2.GetX() * 0.5f;
    float centerPosY2 = rectPos2.GetY() - rectSize2.GetY() * 0.5f;

    if (centerPosX1 < centerPosX2 + rectSize2.GetX() && 
        centerPosX1 + rectSize1.GetX() > centerPosX2 && 
        centerPosY1 < centerPosY2 + rectSize2.GetY() && 
        rectSize1.GetY() + centerPosY1 > centerPosY2)
    {
        return true; 
    }
    return false;
}

bool Collider::checkRectPixels(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize) const
{
	//calculate rect collision area
	int rectCollisionWidth = pixelsSize.GetX() / 2 + rectSize.GetX() / 2 - std::abs(rectPos.GetX() - pixelsPos.GetX());
	int rectCollisionHeight = pixelsSize.GetY() / 2 + rectSize.GetY() / 2 - std::abs(rectPos.GetY() - pixelsPos.GetY());

	if (rectCollisionHeight > 0 && rectCollisionWidth > 0)
	{
		int xInit, yInit;

		if (pixelsPos.GetX() < rectPos.GetX())
		{
			//pixelsPos on the left and rect on the right
			xInit = pixelsSize.GetX() - rectCollisionWidth;
		}
		else
		{
			//rect on the left and pixelsPos on the right
			xInit = 0;
		}

		if (pixelsPos.GetY() < rectPos.GetY())
		{
			//pixelsPos on the bottom and rect on the top
			yInit = pixelsSize.GetY() - rectCollisionHeight;
		}
		else
		{
			//rect on the bottom and pixelsPos on the top
			yInit = 0;
		}

		for (int xCount = 0; xCount < rectCollisionWidth; ++xCount)
		{
			for (int yCount = 0; yCount < rectCollisionHeight; ++yCount)
			{
				//for each pixel on the collision region check alpha
				int xCountReal = xCount + xInit;
				int yCountReal = yCount + yInit;

				int pixel = (yCountReal * pixelsSize.GetX() + xCountReal) * 4; //4 color bytes
				uint8_t alpha = pixels[pixel + 3];

				if (alpha)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Collider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1,
    const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2) const
{
	//calculate rect collision area
	int rectCollisionWidth = pixelsSize1.GetX() * 0.5 + pixelsSize2.GetX() * 0.5 - std::abs(pixelsPos1.GetX() - pixelsPos2.GetX());
	int rectCollisionHeight = pixelsSize1.GetY() * 0.5 + pixelsSize2.GetY() * 0.5 - std::abs(pixelsPos1.GetY() - pixelsPos2.GetY());

	if (rectCollisionHeight > 0 && rectCollisionWidth > 0)
	{
		int xInit1, yInit1;
		int xInit2, yInit2;

		if (pixelsPos1.GetX() < pixelsPos2.GetX())
		{
			//pixelsPos1 on the left and pixelsPos2 on the right
			xInit1 = pixelsSize1.GetX() - rectCollisionWidth;
			xInit2 = 0;
		}
		else
		{
			//pixelsPos2 on the left and pixelsPos1 on the right
			xInit1 = 0;
			xInit2 = pixelsSize2.GetX() - rectCollisionWidth;
		}

		if (pixelsPos1.GetY() < pixelsPos2.GetY())
		{
			//pixelsPos1 on the bottom and pixelsPos2 on the top
			yInit1 = pixelsSize1.GetY() - rectCollisionHeight;
			yInit2 = 0;
		}
		else
		{
			//pixelsPos2 on the bottom and pixelsPos1 on the top
			yInit1 = 0;
			yInit2 = pixelsSize2.GetY() - rectCollisionHeight;
		}

		for (int xCount = 0; xCount < rectCollisionWidth; ++xCount)
		{
			for (int yCount = 0; yCount < rectCollisionHeight; ++yCount)
			{
				//for each pixel on the collision region compare with the other sprite equivalent pixel
				int xCountReal1 = xCount + xInit1;
				int yCountReal1 = yCount + yInit1;

				int xCountReal2 = xCount + xInit2;
				int yCountReal2 = yCount + yInit2;

				int pixel1 = (yCountReal1 * pixelsSize1.GetX() + xCountReal1) * 4; //4 color bytes
				uint8_t alpha1 = pixels1[pixel1 + 3];

				int pixel2 = (yCountReal2 * pixelsSize2.GetX() + xCountReal2) * 4; //4 color bytes
				uint8_t alpha2 = pixels2[pixel2 + 3];

				if (alpha1 && alpha2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

Vec2 Collider::getCollisionPos() const
{
    return position;
}

void Collider::setCollisionPos(Vec2 pos)
{
    position = pos;
}

Vec2 Collider::getRectColSize() const
{
    return rectColtSize;
}

void Collider::setRectColSize(Vec2 size)
{
    rectColtSize = size;
}

float Collider::getRadius() const
{
    return radius;
}

void Collider::setRadius(float rad)
{
    radius = rad;
}

int Collider::getColType() const
{
    return colType;
}

void Collider::setColType(int type)
{
    colType = type;
}