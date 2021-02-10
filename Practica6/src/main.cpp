#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stdlib.h>
#include "World.h"

using namespace std;

ltex_t* loadTexture(const char* filename) {

	int glid = 1;
	int xImage;
	int yImage;

	unsigned char* buffer = stbi_load(filename, &xImage, &yImage, nullptr, 4); //cargas los datos en buffer

	ltex_t* texture = ltex_alloc(xImage, yImage, glid); //create a struct with the size and glid data

	//the struct is like the following:
	//	typedef struct {
	//		int glid;
	//		int width;
	//		int height;
	//	} ltex_t;

	//Metemos el buffer de pixeles en la GPU (texture)
	ltex_setpixels(texture, buffer);

	//Liberamos el mapa de bits de la memoria una vez tenemos ya el sprite en la GPU
	stbi_image_free(buffer);

	return texture;
}

int main() {

	//inicializar el GLFW.
	if (glfwInit() == GLFW_TRUE)
	{
		int windowWidth = 1020;
		int windowHeight = 720;
		static float previous_seconds = static_cast<float>(glfwGetTime());
		float current_seconds = 0;
		float elapsed_seconds = 0;
		float fDeltaTime = 0;
		const char* sFilePath = "data/bee_anim.png";
		const char* sBackground1 = "data/level.png";
		const char* sBackground2 = "data/trees1.png";
		const char* sBackground3 = "data/trees2.png";
		const char* sBackground4 = "data/clouds.png";
		double dXMouse = 0;
		double dYMouse = 0;
		float fDegrees = 0;

		double delta = glfwGetTime();

		//Crear la ventana y darle un contexto
		GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Abeja Zumbona", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		lgfx_setup2d(windowWidth, windowHeight);

		//Cargamos la textura entera abeja.
		ltex_t* fullTexture = loadTexture(sFilePath);
		Sprite mySprite(fullTexture);
		mySprite.setPosition(Vec2(windowWidth * 0.5f, windowHeight * 0.5f));

		//Cargamos las texturas de fondo.
		ltex_t* texturaBackground1 = loadTexture(sBackground1);
		Sprite mySpriteBackground1(texturaBackground1);
		mySpriteBackground1.setPosition(Vec2(0.f, 0.f));

		ltex_t* texturaBackground2 = loadTexture(sBackground2);
		Sprite mySpriteBackground2(texturaBackground2);
		mySpriteBackground2.setPosition(Vec2(0.f, 0.f));

		ltex_t* texturaBackground3 = loadTexture(sBackground3);
		Sprite mySpriteBackground3(texturaBackground3);
		mySpriteBackground3.setPosition(Vec2(0.f, -100.f));

		ltex_t* texturaBackground4 = loadTexture(sBackground4);
		Sprite mySpriteBackground4(texturaBackground4);
		mySpriteBackground4.setPosition(Vec2(0.f, 0.f));

		//Creamos un World.
		World myWorld;

		Background* back0 = new Background(&mySpriteBackground1, myWorld.getScrollRatio(0), myWorld.getScrollSpeed(0));
		Background* back1 = new Background(&mySpriteBackground2, myWorld.getScrollRatio(1), myWorld.getScrollSpeed(1));
		Background* back2 = new Background(&mySpriteBackground3, myWorld.getScrollRatio(2), myWorld.getScrollSpeed(2));
		Background* back3 = new Background(&mySpriteBackground4, myWorld.getScrollRatio(3), myWorld.getScrollSpeed(3));

		myWorld.bee = &mySprite;
		myWorld.listBackgrounds[0] = back0;
		myWorld.listBackgrounds[1] = back1;
		myWorld.listBackgrounds[2] = back2;
		myWorld.listBackgrounds[3] = back3;

		while (!glfwWindowShouldClose(window))
		{
			window = glfwGetCurrentContext();
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			lgfx_setup2d(windowWidth, windowHeight); //Area que pintamos. Si no lo ponemos pintará en toda la ventana

			current_seconds = static_cast<float>(glfwGetTime());
			elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;

			fDeltaTime += elapsed_seconds;
			glfwGetCursorPos(window, &dXMouse, &dYMouse);

			myWorld.update(&fDeltaTime, elapsed_seconds, dXMouse, dYMouse);
			myWorld.draw(Vec2(windowWidth, windowHeight));

			//Clear buffer
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();

		return 0;
	}
		

    return 0;
}
