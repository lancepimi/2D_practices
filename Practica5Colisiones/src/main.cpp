#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
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
		const char* sBallPath = "data/ball.png";
		const char* sBeePath = "data/bee.png";
		const char* sBoxPath = "data/box.png";
		const char* sCirclePath = "data/circle.png";
		const char* sRectPath = "data/rect.png";
		double dXMouse = 0;
		double dYMouse = 0;
		float scaleValue = 1.f;
		float scaleVelocity = 0.25f;

		//Crear la ventana y darle un contexto
		GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Colisioname Esta", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		lgfx_setup2d(windowWidth, windowHeight);

		vector<Sprite*> SpriteColliders;
	    vector<Sprite*> SpriteMouseColliders;

		/*********** CARGA DE SPRITES ***********/
		//Cargamos el balon
		ltex_t* fullTexture = loadTexture(sBallPath);
		Sprite* BallSprite = new Sprite(fullTexture, COLLISION_CIRCLE, Vec2(windowWidth * 0.25, windowHeight * 0.5), "Ball");
		SpriteColliders.push_back(BallSprite); //añadimos al vector los sprites creados

		//Cargamos la abeja
		fullTexture = loadTexture(sBeePath);
		Sprite* BeeSprite = new Sprite(fullTexture, COLLISION_PIXELS, Vec2((windowWidth * 0.25) * 2, windowHeight * 0.5), "Bee");
		SpriteColliders.push_back(BeeSprite);

		//Cargamos el caja
		fullTexture = loadTexture(sBoxPath);
		Sprite* BoxSprite = new Sprite(fullTexture, COLLISION_RECT, Vec2((windowWidth * 0.25) * 3, windowHeight * 0.5), "Box");
		SpriteColliders.push_back(BoxSprite);

		//Cargamos las texturas del mouse
		ltex_t* circleMouse = loadTexture(sCirclePath);
		ltex_t* rectMouse = loadTexture(sRectPath);
		ltex_t* beeMouse = loadTexture(sBeePath);
		Sprite* MouseSprite = new Sprite(circleMouse, COLLISION_CIRCLE, Vec2(windowWidth, windowHeight), "Mouse");
		SpriteMouseColliders.push_back(MouseSprite);

		while (!glfwWindowShouldClose(window))
		{
			/** VENTANA **/
		    window = glfwGetCurrentContext();
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			lgfx_setup2d(windowWidth, windowHeight); //Area que pintamos. Si no lo ponemos pintará en toda la ventana

			/** TIEMPO**/
			current_seconds = static_cast<float>(glfwGetTime());
			elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;
			fDeltaTime += elapsed_seconds;

			double delta = glfwGetTime();

			//Posicioón Ratón
		    glfwGetCursorPos(window, &dXMouse, &dYMouse);
	
			//Limpiamos el fondo
			lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);

			//redimensionar sprites
			scaleValue += scaleVelocity * elapsed_seconds;
			scaleValue = Sprite::clamp(scaleValue, 1.1f, 0.9f);

			if (abs(scaleValue - 0.9f) <= 0.001f)
			{
				scaleVelocity = -scaleVelocity;
			}
			else if (abs(scaleValue - 1.1f) <= 0.001f)
			{
				scaleVelocity = -scaleVelocity;
			}

			BallSprite->setScale(Vec2(scaleValue, scaleValue));
			BoxSprite->setScale(Vec2(scaleValue, scaleValue));

			/** MOUSE **/
			MouseSprite->update(&fDeltaTime, elapsed_seconds, &dXMouse, &dYMouse);

			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
			{
				MouseSprite->setCollisionType(COLLISION_CIRCLE);
				MouseSprite->setTexture(circleMouse);
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			{
				MouseSprite->setCollisionType(COLLISION_RECT);
				MouseSprite->setTexture(rectMouse);
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
			{
				MouseSprite->setCollisionType(COLLISION_PIXELS);
				MouseSprite->setTexture(beeMouse);
			}

			/**** COLISIONES ****/
		    for (Sprite* element : SpriteColliders)
            {
				for (Sprite* element2 : SpriteMouseColliders)
				{
					if (element->m_collider->collides(*element2->m_collider))
					{
						printf("collision CircleCircle\n");
						element->setColor(1, 0, 0, 0.8);
					}
					else
					{
						element->setColor(1, 1, 1, 1);
					}
				}
            }

			/** PINTADO **/
			BallSprite->draw();
			BeeSprite->draw();
			BoxSprite->draw();
			MouseSprite->draw();

			//Clear buffer
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// Liberamos las texturas
		ltex_free(fullTexture);
		glfwTerminate();

		return 0;
	}
		

    return 0;
}
