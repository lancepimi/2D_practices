#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
	:x(0)
	,y(0)
{
}

Vec2::Vec2(float _fX, float _fY)
	: x(_fX)
	, y(_fY)
{
}

float Vec2::GetX() const
{
	return x;
}

float Vec2::GetY() const
{
	return y;
}

void Vec2::SetX(float _fX)
{
	x = _fX;
}

void Vec2::SetY(float _fY)
{
	y = _fY;
}

Vec2  Vec2::Sum(Vec2 _v)
{
	Vec2 resultado(x + _v.x, y + _v.y);
	return  resultado;
}

Vec2 Vec2::SumScalar(float _fX)
{
	Vec2 resultado(x + _fX, y + _fX);
	return resultado;
}

Vec2 Vec2::Sub(Vec2 _v)
{
	Vec2 resultado(x - _v.x, y - _v.y);
	return resultado;
}

Vec2 Vec2::SubScalar(float _fX)
{
	Vec2 resultado(x - _fX, y - _fX);
	return resultado;
}

Vec2 Vec2::Product(float _fX)
{
	Vec2 resultado(x * _fX, y * _fX);
	return resultado;
}

float Vec2::Dot(Vec2 _v)
{
	float resultado(x * _v.x + y * _v.y);
	return resultado;
}

Vec2 Vec2::Division(float _fX)
{
	return Vec2(x / _fX, y / _fX);
}

float Vec2::Abs()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vec2::Length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::Normal() //Normalizar el Vector
{
	float fLongitud = this->Length();
	return Vec2(x / fLongitud, y / fLongitud);
}

float Vec2::angle(const Vec2& other) const
{
	return atan2f(other.y - y, other.x - x) * 57.2957795;
}

float Vec2::dist(const Vec2& other) const
{
	return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}