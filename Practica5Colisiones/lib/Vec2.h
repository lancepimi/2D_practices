#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float _fX, float _fY);

	float GetX() const;
	float GetY() const;

	void SetX(float _fX);
	void SetY(float _fY);

	Vec2 Suma(Vec2 _v);
	Vec2 SumaEscalar(float _fX);

	Vec2 Resta(Vec2 _v);
	Vec2 RestaEscalar(float _fX);

	Vec2 Producto(float _fX);
	float ProductoEscalar(Vec2 _v);

	Vec2 Division(float _fX);

	float ValorAbsoluto();
	float Length(const Vec2& v);
	Vec2 Normal();

	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;

	
private:
	float m_fX;
	float m_fY;
};