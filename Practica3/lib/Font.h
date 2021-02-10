
#include "Vec2.h"
#include "stb_truetype.h"
#include <litegfx.h>
#include <glfw3.h>
#include <stb_image.h> 
#include <vector>
#include "stdio.h"
#include <iostream>

class Font
{
private:
	float fTextHeight = 0; 
	const char * filename;
	ltex_t* textura = nullptr;
	stbtt_bakedchar* charData = nullptr;
	Vec2 textSize;
	
public:

	float fX = 0;
	float fY = 0;
	float fVelocity = 2.f;
	float colorX = ((double)rand() / (RAND_MAX));
	float colorY = ((double)rand() / (RAND_MAX));
	float colorZ = ((double)rand() / (RAND_MAX));
	
	Font();
	Font(float _fTextHeight, ltex_t* _textura, stbtt_bakedchar* _chardata);

	static Font* load(const char* _filename, float _fTextHeight);

	float getHeight() const;
	
	Vec2 getTextSize(const char* text);
	
	void draw(const char* text, const Vec2& pos) const;

	void moveLeft();

	bool destroyFont(Vec2& posActual);

};