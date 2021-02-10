#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
	:m_fX(0)
	,m_fY(0)
{
}

Vec2::Vec2(float _fX, float _fY)
	: m_fX(_fX)
	, m_fY(_fY)
{
}

float Vec2::GetX() const
{
	return m_fX;
}

float Vec2::GetY() const
{
	return m_fY;
}

void Vec2::SetX(float _fX)
{
	m_fX = _fX;
}

void Vec2::SetY(float _fY)
{
	m_fY = _fY;
}

Vec2  Vec2::Suma(Vec2 _v)
{
	Vec2 resultado(m_fX + _v.m_fX, m_fY + _v.m_fY);
	return  resultado;
}

Vec2 Vec2::SumaEscalar(float _fX)
{
	Vec2 resultado(m_fX + _fX, m_fY + _fX);
	return resultado;
}

Vec2 Vec2::Resta(Vec2 _v)
{
	Vec2 resultado(m_fX - _v.m_fX, m_fY - _v.m_fY);
	return resultado;
}

Vec2 Vec2::RestaEscalar(float _fX)
{
	Vec2 resultado(m_fX - _fX, m_fY - _fX);
	return resultado;
}

Vec2 Vec2::Producto(float _fX)
{
	Vec2 resultado(m_fX * _fX, m_fY * _fX);
	return resultado;
}

float Vec2::ProductoEscalar(Vec2 _v)
{
	float resultado(m_fX * _v.m_fX + m_fY * _v.m_fY);
	return resultado;
}

Vec2 Vec2::Division(float _fX)
{
	return Vec2(m_fX / _fX, m_fY / _fX);
}

float Vec2::ValorAbsoluto()
{
	return sqrt(pow(m_fX, 2) + pow(m_fY, 2));
}

float Vec2::Longitud()
{
	return sqrt(pow(m_fX, 2) + pow(m_fY, 2));
}

Vec2 Vec2::Normal() //Normalizar el Vector
{
	float fLongitud = this->Longitud();
	return Vec2(m_fX / fLongitud, m_fY / fLongitud);
}

float Vec2::angle(const Vec2& other) const
{
	return atan2f(other.m_fY - m_fY, other.m_fX - m_fX) * 57.2957795;
}

float Vec2::distance(const Vec2& other) const
{
	return sqrt(pow(other.m_fX - m_fX, 2) + pow(other.m_fY - m_fY, 2));
}