
#include "Font.h"


using namespace std;

Font::Font()
	: fTextHeight(0)
	, textura(nullptr)
	, charData(nullptr)
{

}

Font::Font(float _fHeight, ltex_t* _textura, stbtt_bakedchar* _chardata)
	: fTextHeight(_fHeight)
	, textura(_textura)
	, charData(_chardata)
{

}

Font* Font::load(const char* _filename, float _fHeight)
{
	int iTextureWidth = 512, iTextureHeight = 512;
	unsigned char* tempPixelsAlphaBuffer = new unsigned char[512 * 512];
	unsigned char* tempPixelsColorBuffer = new unsigned char[512 * 512 * 4];
	stbtt_bakedchar* chardata = new stbtt_bakedchar[128]; // all the ASCII table (0 - 127)

	FILE* pFile(nullptr);
	fopen_s(&pFile, _filename, "rb");

	if (pFile != nullptr)
	{
		fseek(pFile, 0, SEEK_END); //Ponemos el puntero del fichero al final.
		const unsigned int uSizeBuffer = ftell(pFile); //Nos dice el tamano de bytes que hay desde el principio del fichero hasta donde este el puntero actualmente.
		fseek(pFile, 0, SEEK_SET); //Devolvemos el puntero al principio.

		unsigned char* sBuffer;

		sBuffer = (unsigned char*)malloc(sizeof(unsigned char) * uSizeBuffer);
		fread(sBuffer, sizeof(unsigned char), uSizeBuffer, pFile);
		
		stbtt_BakeFontBitmap(

			sBuffer, //Archivo ttf despues del read
			0, //Siempre 0
			_fHeight, //Tamano que queremos que tenga CADA letra (tamano de fuente).
			tempPixelsAlphaBuffer, //Altura * Anchura. Tamano total de la imagen cargada con todo que queremos. Obtenemos los alfas
			iTextureWidth, //Anchura para que entre todo. Dependiendo del tamano de fuente que le demos, tendremos que darle una altura y anchura para que entren todas las letras.
			iTextureHeight, //Altura para que entre todo.
			0, //Ultimo caracter a renderizar (ASCII)
			127, //Ultimo caracter a renderizar
			chardata 	//Puntero donde guardara la informacion de los glifos.
		);

		//Convertimos el buffer con el alpha en un buffer de color(RGBA). 255, 255, 255, ALPHA
		int j = 0;
		for (int i = 0; i < (512 * 512); i++)
		{
			tempPixelsColorBuffer[j] = 255;
			j++;
			tempPixelsColorBuffer[j] = 255;
			j++;
			tempPixelsColorBuffer[j] = 255;
			j++;
			tempPixelsColorBuffer[j] = tempPixelsAlphaBuffer[i];
			j++;
		}
		
		fclose(pFile);

		ltex_t* texture = ltex_alloc( iTextureWidth, iTextureHeight, 1); //creas un struct con los datos del tamaño y glid

		//Estructura:
		//typedef struct {
		//	int glid;
		//	int width;
		//	int height;
		//} ltex_t;

		ltex_setpixels( texture, tempPixelsColorBuffer);

		return new Font( _fHeight, texture, chardata);
	}
	else
	{
		return nullptr;
	}


}
	
float Font::getHeight() const
{
	return  fTextHeight;
}

Vec2 Font::getTextSize(const char* text)
{
	float fPosX = fX;
	float fPosY = fY;
	float fSizeX = 0;
	float fSizeY = 0;

	while (*text)
	{
		if (*text >= 0 && *text < 128)
		{
			stbtt_aligned_quad textureDrawInfo; //Puntero donde colocará información del rectángulo a dibujar. 
			//Obtiene el rectángulo en el que renderizar un determinado caracter.
			stbtt_GetBakedQuad
			(charData, //Buffer de glifos rellenado por stbtt_BakeFontBitmap. 
				512, //Tamaño de la textura de la fuente. 
				512, //Tamaño de la textura de la fuente. 
				*text - 0, //Código del carácter menos el valor de first_char pasado a stbtt_BakeFontBitmap
				&fPosX, &fPosY, //Puntero a las coordenadas donde queremos dibujar el carácter. Actualizará el valor para indicar las coordenadas donde se debería dibujar el siguiente carácter del texto
				&textureDrawInfo, //Puntero donde colocará información del rectángulo a dibujar
				true);

			//Guardamos el tamano que ocupa el texto en pantalla.
			fSizeX += (textureDrawInfo.x1 - textureDrawInfo.x0);
			fSizeY = (textureDrawInfo.y1 - textureDrawInfo.y0);

		}
		++text;
	}
	textSize = Vec2(fSizeX, fSizeY);
	return textSize;
}

void Font::draw(const char* text, const Vec2 & pos) const
{
	float fPosX = pos.GetX();
	float fPosY = pos.GetY();

	while (*text)
	{
		if (*text >= 0 && *text < 128)
		{
			stbtt_aligned_quad textureDrawInfo; //Puntero donde colocará información del rectángulo a dibujar. 
			//Obtiene el rectángulo en el que renderizar un determinado caracter.
			stbtt_GetBakedQuad
			(charData, 512, 512,
				*text - 0, //Caracter a dibujar
				&fPosX, &fPosY, //Variable de salida de las siguientes X e Y a dibujar
				&textureDrawInfo, //Variabe de salida del rectangulo a dibujar
				true);

			//Dibujamos la textura del caracter.
			ltex_drawrotsized
			(textura, textureDrawInfo.x0, textureDrawInfo.y0,
				0.f, 0.f, 0.f,
				textureDrawInfo.x1 - textureDrawInfo.x0, textureDrawInfo.y1 - textureDrawInfo.y0,
				textureDrawInfo.s0, textureDrawInfo.t0, textureDrawInfo.s1, textureDrawInfo.t1);
		}
		++text;

	}
}

//void Font::moveLeft()
//{
//	//TODO move letters
//	fX--;
//}

bool Font::destroyFont(Vec2 & posActual)
{
	if (posActual.GetX() <= (-1 * textSize.GetX()))
	{
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}