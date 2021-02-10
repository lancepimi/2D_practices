#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stdlib.h>
#include "Sprite.h"

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
		double dXMouse = 0;
		double dYMouse = 0;
		float fDegrees = 0;

		double delta = glfwGetTime();

		//Crear la ventana y darle un contexto
		GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Abeja Zumbona", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		lgfx_setup2d(windowWidth, windowHeight);

		//Cargamos la textura entera.
		ltex_t* fullTexture = loadTexture(sFilePath);
		Sprite mySprite(fullTexture);
		mySprite.setPosition(Vec2(windowWidth/2, windowHeight/2));

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
			
			//Limpiamos el fondo
			lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

			mySprite.update(&fDeltaTime, elapsed_seconds, &dXMouse, &dYMouse);
			mySprite.draw();

			//Clear buffer
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();

		return 0;
	}
		

    return 0;
}
