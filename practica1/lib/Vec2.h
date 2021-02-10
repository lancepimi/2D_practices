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

	Vec2 Sum(Vec2 _v);
	Vec2 SumScalar(float _fX);

	Vec2 Sub(Vec2 _v);
	Vec2 SubScalar(float _fX);

	Vec2 Product(float _fX);
	float Dot(Vec2 _v);

	Vec2 Division(float _fX);

	float Abs();
	float Length();
	Vec2 Normal();

	float angle(const Vec2& other) const;
	float dist(const Vec2& other) const;

	
private:
	float x;
	float y;
};