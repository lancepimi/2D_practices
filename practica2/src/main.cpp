
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <stb_image.h>

using namespace std;

int width = 1500, height = 900;
double cursorX, cursorY;
bool fireDirection = true, fireMultiplierDirection = true;
float fireAngle = 0, fireMultiplier = 1;

const char* wall = "data/wall.jpg";
const char* fire = "data/fire.png";
const char* grille = "data/grille.png";
const char* light = "data/light.png";

ltex_t* loadTexture(const char* filename) {

	int glid = 0;
	int xImage = 0;
	int yImage = 0;

	unsigned char* buffer = stbi_load(filename, &xImage, &yImage, nullptr, 4); //cargas los datos en buffer

	ltex_t* texture = ltex_alloc(xImage, yImage, glid); //create a struct with the size and glid data

	//the struct is like the following:
	//	typedef struct {
	//		int glid;
	//		int width;
	//		int height;
	//	} ltex_t;

	ltex_setpixels(texture, buffer);

	stbi_image_free(buffer);

	return texture;
}

int main() {

	int init = glfwInit();
	double delta = glfwGetTime();

	GLFWwindow* window = glfwCreateWindow(width, height, "llamita de la muerte", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	lgfx_setup2d(width, height);


	ltex_t* wallTexture = loadTexture(wall);
	ltex_t* grilleTexture = loadTexture(grille);
	ltex_t* fireTexture = loadTexture(fire);
	ltex_t* lightTexture = loadTexture(light);

	while (!glfwWindowShouldClose(window))
	{

		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

		//paint wall
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(wallTexture, 0, 0, 0, 0, 0, width, height, 0, 0, (width / wallTexture->width), (height / wallTexture->height));
		
		//set angle and multiplier of light
		glfwGetCursorPos(window, &cursorX, &cursorY);
		if (fireDirection == true)
		{
			fireAngle += 10 * delta;
		}
		else
		{
			fireAngle -= 10 * delta;
		}

		if (fireAngle >= 10)
		{
			fireDirection = false;
		}

		if (fireAngle <= -10)
		{
			fireDirection = true;
		}

		if (fireMultiplierDirection == true)
		{
			fireMultiplier += 0.5f * delta;
		}
		else
		{
			fireMultiplier -= 0.5f * delta;
		}

		if (fireMultiplier <= 0.8f)
		{
			fireMultiplierDirection = true;
		}

		if (fireMultiplier >= 1.2f)
		{
			fireMultiplierDirection = false;
		}

		//paint fire
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(fireTexture, cursorX + (fireTexture->width/ 2), cursorY + (fireTexture->height/2), fireAngle, fireMultiplier, fireMultiplier, fireTexture->width, fireTexture->height, 0, 0, 1, 1);
		
		//paint grille
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(grilleTexture, 0, 0, 0, 0, 0, width, height, 0, 0, width/ fireTexture->width, height/ fireTexture->height);
		
		//paint light
		lgfx_setblend(BLEND_MUL);
		ltex_draw(lightTexture, cursorX - (lightTexture->width) / 2, cursorY - (lightTexture->height) / 2);
		
		//fill the light gaps with black
		ltex_drawrotsized(lightTexture, cursorX - (lightTexture->width/2), cursorY - (lightTexture->height/2), 0, 0, 0, width*(-2.5), height*2.5, 1, 1, 1, 1);
		ltex_drawrotsized(lightTexture, cursorX + (lightTexture->width/2), cursorY + (lightTexture->height/2), 0, 0, 0, width*2.5, height*(-2.5), 1, 1, 1, 1);
		ltex_drawrotsized(lightTexture, cursorX - (lightTexture->width/2), cursorY + (lightTexture->height/2), 0, 0, 0, width*2.5, height*2.5, 1, 1, 1, 1);
		ltex_drawrotsized(lightTexture, cursorX + (lightTexture->width/2), cursorY - (lightTexture->height/2), 0, 0, 0, width*(-2.5), height*(-2.5), 1, 1, 1, 1);

		//Clear buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



