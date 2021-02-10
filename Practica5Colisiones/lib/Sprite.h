#pragma once
#include <litegfx.h>
#include "Vec2.h"
#include "stb_truetype.h"
#include <glfw3.h>
#include <stb_image.h>

#include "CircleCollider.h"
#include "RectCollider.h"

#include "Collider.h"

enum CollisionType {
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};

class Sprite
{
private:
	const ltex_t* texture = nullptr;
	lblend_t mode = BLEND_ALPHA;
    const char* textureName;

	float fGreen = 0.f;
	float fRed = 0.f;
	float fBlue = 0.f;
	float fAlpha = 1.f;

	Vec2 vecPosition;
	Vec2 vecMousePosition;
	Vec2 colPosition;
	Vec2 scale;

	CollisionType Collision = COLLISION_NONE;

public:
	Collider* m_collider;

	typedef void (*CallbackFunc)(Sprite&, float);
	
	// Indicamos el número de frames en horizontal y vertical que tendrá la imagen del sprite
	Sprite(const ltex_t* texture, CollisionType type, Vec2 pos, const char* name, float _hframes = 8, float _vframes = 1);

	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* texture, int hframes = 8, int vframes = 1);

	lblend_t getBlend() const;
	void setBlend(lblend_t mode);

	const char* GetTextureName() const;

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);

	const Vec2& getPosition() const;
	void setPosition(const Vec2& pos);
	const int getDirection() const;
	void setDirection(int _iNewDirection);

	float getAngle() const;
	void setAngle(float angle);

	const Vec2& getScale() const;
	void setScale(const Vec2& scale);

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2& getPivot() const;
	void setPivot(const Vec2& pivot);
	
	float getHframes() const;
	float getVframes() const;

	// Veces por segundo que se cambia el frame de animación
	int getFps() const;
	void setFps(int fps);
	
	// Frame actual de animación
	float getCurrentFrame() const;
	void setCurrentFrame(float frame);

	//Collisions
	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;

	const Vec2& getColPosition() const;
	void setColPosition(const Vec2& pos);

	const Collider* getCollider() const;
    bool collides(const Sprite& other) const;

	static double clamp(double x, double upper, double lower);

	void update(float* deltaTime, float elapsed_seconds, double* dxMouse, double* dYMouse);
	
	void draw() const;
};
