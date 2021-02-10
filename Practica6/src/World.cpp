#include "World.h"
#include "Vec2.h"

float clamp(float v, float lo, float hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

World::World()
{
}

float World::getClearRed() const
{
	return clearRed;
}

float World::getClearGreen() const
{
	return clearGreen;
}

float World::getClearBlue() const
{
	return clearBlue;
}

const ltex_t* World::getBackground(size_t layer) const
{
	return listBackgrounds[layer]->m_sprite->getTexture();
}

float World::getScrollRatio(size_t layer) const
{
	return scrollRatios[layer];
}

void World::setScrollRatio(size_t layer, float ratio)
{
	scrollRatios[layer] = ratio;
}

const Vec2& World::getScrollSpeed(size_t layer) const
{
	return backSpeeds[layer];
}

void World::setScrollSpeed(size_t layer, const Vec2& speed)
{
	backSpeeds[layer] = speed;
}

const Vec2& World::getCameraPosition() const
{
	return cameraPosition;
}

void World::setCameraPosition(const Vec2& pos)
{
	cameraPosition = pos;
}


void World::update(float* deltaTime, float elapsed_seconds, double dXMouse, double dYMouse)
{
	bee->update(deltaTime, elapsed_seconds, dXMouse, dYMouse, m_camPos);

	for (int i = 0; i < 4; i++)
	{
		if (i == 3)
		{
			listBackgrounds[3]->m_sprite->setPosition(Vec2(listBackgrounds[3]->m_sprite->getPosition().GetX() + (1 - listBackgrounds[3]->m_fScrollRatio) * listBackgrounds[3]->m_vec2ScrollVel.GetX() * elapsed_seconds,
				listBackgrounds[3]->m_sprite->getPosition().GetY() + (1 - listBackgrounds[3]->m_fScrollRatio) * listBackgrounds[3]->m_vec2ScrollVel.GetY() * elapsed_seconds));
		}
		else
		{
			listBackgrounds[i]->m_sprite->setPosition(Vec2(-m_camPos->GetX() * listBackgrounds[i]->m_fScrollRatio, listBackgrounds[i]->m_sprite->getPosition().GetY()));
		}
	}
}

void World::draw(Vec2& screenSize)
{
	//Actualizar posicin de la camara para centrar la abeja
	m_camPos->SetX(clamp(bee->getPosition().GetX() - screenSize.GetX() * 0.5f, 0, listBackgrounds[0]->m_sprite->getTexture()->width - screenSize.GetX()));
	m_camPos->SetY(clamp(bee->getPosition().GetY() - screenSize.GetY() * 0.5f, 0, listBackgrounds[0]->m_sprite->getTexture()->height - screenSize.GetY()));
	lgfx_setorigin(m_camPos->GetX(), m_camPos->GetY());
	lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);
	lgfx_setblend(BLEND_ALPHA);


	//Nubes
	for (float fNewX = m_camPos->GetX() * (1 - listBackgrounds[0]->m_fScrollRatio) + listBackgrounds[3]->m_sprite->getPosition().GetX(); fNewX < listBackgrounds[0]->m_sprite->getTexture()->width; fNewX += listBackgrounds[3]->m_sprite->getTexture()->width)
	{
		for (float fNewY = m_camPos->GetY() * (1 - listBackgrounds[0]->m_fScrollRatio) + listBackgrounds[3]->m_sprite->getPosition().GetY(); fNewY < listBackgrounds[0]->m_sprite->getTexture()->height; fNewY += listBackgrounds[3]->m_sprite->getTexture()->height)
		{
			ltex_drawrotsized(listBackgrounds[3]->m_sprite->getTexture(), fNewX, fNewY,
				0, 0, 0,
				listBackgrounds[3]->m_sprite->getTexture()->width, listBackgrounds[3]->m_sprite->getTexture()->height,
				0, 0, 1, 1);
		}
	}

	//Resto de fondos
	for (int iLevelWidht = 0; iLevelWidht < (listBackgrounds[0]->m_sprite->getTexture()->width + 2 * screenSize.GetX()); iLevelWidht += listBackgrounds[2]->m_sprite->getTexture()->width)
	{
		ltex_drawrotsized(listBackgrounds[2]->m_sprite->getTexture(), listBackgrounds[2]->m_sprite->getPosition().GetX() + iLevelWidht, listBackgrounds[2]->m_sprite->getPosition().GetY(),
			0, 0.f, 0.f,
			listBackgrounds[2]->m_sprite->getTexture()->width, listBackgrounds[2]->m_sprite->getTexture()->height,
			0, 0, 1, 1);
	}

	for (int iLevelWidht = 0; iLevelWidht < listBackgrounds[0]->m_sprite->getTexture()->width + 2 * screenSize.GetX(); iLevelWidht += listBackgrounds[1]->m_sprite->getTexture()->width)
	{
		ltex_drawrotsized(listBackgrounds[1]->m_sprite->getTexture(), listBackgrounds[1]->m_sprite->getPosition().GetX() + iLevelWidht, listBackgrounds[1]->m_sprite->getPosition().GetY(),
			0, 0.f, 0.f,
			listBackgrounds[1]->m_sprite->getTexture()->width, listBackgrounds[1]->m_sprite->getTexture()->height,
			0, 0, 1, 1);
	}

	ltex_drawrotsized(listBackgrounds[0]->m_sprite->getTexture(), 0, 0,
		0, 0.f, 0.f,
		listBackgrounds[0]->m_sprite->getTexture()->width, listBackgrounds[0]->m_sprite->getTexture()->height,
		0, 0, 1, 1);

	//Pintamos la abeja
	bee->draw();
}
