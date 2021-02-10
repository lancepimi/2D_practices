#include "Sprite.h"

#include <iostream>

Sprite::Sprite(const ltex_t* _tex, float _hFrames, float _vFrames)
{
	texture = _tex;
	hFrames = _hFrames;
	vFrames = _vFrames;
}

const ltex_t* Sprite::getTexture() const
{
	return texture;
}

lblend_t Sprite::getBlend() const
{
	return mode;
}

void Sprite::setBlend(lblend_t _mode)
{
	mode = _mode;
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

const int Sprite::getDirection() const
{
	return iDirection;
}

void Sprite::setDirection(int _iNewDirection) 
{
	iDirection = _iNewDirection;
}

float Sprite::getHframes() const
{
	return hFrames;
}

float Sprite::getVframes() const
{
	return vFrames;
}

int Sprite::getFps() const
{
	return iFPS;
}

void Sprite::setFps(int fps)
{
	iFPS = fps;
}

float Sprite::getCurrentFrame() const
{
	return iCurrentFrame;
}

void Sprite::setCurrentFrame(float frame)
{
	iCurrentFrame = frame;
}


void Sprite::update(float* deltaTime, float elapsed_seconds, double dXMouse, double dYMouse, Vec2* camPos)
{
	if (*deltaTime >= (1.f / 8.f)) //Cuando lleguemos a 1/8 acumulado, pasamos al siguiente Frame.
	{
		*deltaTime = 0.f;
		if(iCurrentFrame == 8.f)
		{
			iCurrentFrame = 0.f;
		}
		//Sabemos que todas las imagenes tienen el mismo ancho
		UBegin = iCurrentFrame * ( 1.f / hFrames);
		UEnd = (iCurrentFrame + 1.f) * (1.f / hFrames);
		iCurrentFrame++;
		//Las V en este caso son constantes ya que el sprite solamente tiene una fila
	}

	vecMousePosition = Vec2(dXMouse, dYMouse);

	//Movimiento de la abeja según donde está el ratón
	//(+,+)
	if( vecPosition.GetX() - camPos->GetX() < vecMousePosition.GetX() && vecPosition.GetY() < vecMousePosition.GetY())
	{
		setPosition(Vec2(vecPosition.GetX() + 128 * elapsed_seconds, vecPosition.GetY() + 128 * elapsed_seconds));
		iDirection = 1;

		if(fAngle > -15)
			fAngle -= 32 * elapsed_seconds;
	}
	//(+,-)
	if( vecPosition.GetX() - camPos->GetX() < vecMousePosition.GetX() && vecPosition.GetY() > vecMousePosition.GetY())
	{
		setPosition(Vec2(vecPosition.GetX() + 128 * elapsed_seconds, vecPosition.GetY() - 128 * elapsed_seconds));
		iDirection = 1;

		if (fAngle < 15)
			fAngle += 32 * elapsed_seconds;
	}
	//(-,+)
	if( vecPosition.GetX() - camPos->GetX() > vecMousePosition.GetX() && vecPosition.GetY() < vecMousePosition.GetY())
	{
		setPosition(Vec2(vecPosition.GetX() - 128 * elapsed_seconds, vecPosition.GetY() + 128 * elapsed_seconds));
		iDirection = -1;
		
		if (fAngle < 15)
			fAngle += 32 * elapsed_seconds;
	}
	//(-,-)
	if( vecPosition.GetX() - camPos->GetX() > vecMousePosition.GetX() && vecPosition.GetY() > vecMousePosition.GetY())
	{
		setPosition(Vec2(vecPosition.GetX() - 128 * elapsed_seconds, vecPosition.GetY() - 128 * elapsed_seconds));
		iDirection = -1;
		
		if (fAngle > -15)
			fAngle -= 32 * elapsed_seconds;
	}

	//Si la abeja está quieta volvemos al angulo 0
	if(fabs(vecPosition.GetX() - vecMousePosition.GetX()) < 2.f || fabs(vecPosition.GetY() - vecMousePosition.GetX()) < 2.f)
	{
		if(fAngle > 1.f)
			fAngle -= 32 * elapsed_seconds;
		if(fAngle < 1.f)
			fAngle += 32 * elapsed_seconds;
		if(fAngle < 1.f && fAngle > -1.f)
			fAngle = 0;
	}
}

void Sprite::draw() const
{
	lgfx_setblend(mode);
	ltex_drawrotsized(texture, vecPosition.GetX(), vecPosition.GetY(), fAngle, 0.5f, 0.5f,	(texture->width) * (1.f / hFrames) * iDirection, (texture->height) * (1.f / vFrames) , UBegin, VBegin, UEnd, VEnd);
}
