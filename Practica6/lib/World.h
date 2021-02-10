#pragma once

#include "Background.h"


class World
{
	float clearRed = 0.15f;
	float clearGreen = 0.15f;
	float clearBlue = 0.5f;
	const ltex_t* back0 = nullptr;
	const ltex_t* back1 = nullptr;
	const ltex_t* back2 = nullptr;
	const ltex_t* back3 = nullptr;

	Vec2 cameraPosition;
	float scrollRatios[4] = { 0.4, 0.6, 0.8, 1 };
	Vec2 backSpeeds[4] = { Vec2(0,0), Vec2(0,0), Vec2(0,0), Vec2(-16,-8) };

public:
	World();

	Vec2* m_camPos = new Vec2(0.f, 0.f);
	Sprite* bee = nullptr;
	Background* listBackgrounds[4];

	float getClearRed() const;
	float getClearGreen() const;
	float getClearBlue() const;

	const ltex_t* getBackground(size_t layer) const;
	void setBackground(size_t layer, ltex_t* texture);

	float getScrollRatio(size_t layer) const;
	void setScrollRatio(size_t layer, float ratio);

	const Vec2& getScrollSpeed(size_t layer) const;
	void setScrollSpeed(size_t layer, const Vec2& speed);

	const Vec2& getCameraPosition() const;
	void setCameraPosition(const Vec2& pos);

	void addSprite(Sprite& sprite);
	//void removeSprite(Sprite& sprite);

	void update(float* deltaTime, float elapsed_seconds, double dXMouse, double dYMouse);
	void draw(Vec2& screenSize);
};