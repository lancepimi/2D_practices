
#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "vec2.h"
#include <sstream>

using namespace std;

template <typename T>
std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}

int width = 640, height = 480;
float squareSide = 30.f;


int main() {

	int init = glfwInit();

	const double pi = 3.14159265358979323846;
	double delta = glfwGetTime();
	double xMousePosition, yMousePosition;
	float radioOrbit;
	double xCirclePosition;
	double yCirclePosition;
	float angle = 0.f;
	Vec2 screenCenter(width/2, height/2);

	GLFWwindow* window = glfwCreateWindow(width, height, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	lgfx_setup2d(width, height);

	while (!glfwWindowShouldClose(window))
	{
		static float previous_seconds = static_cast<float>(glfwGetTime());
		float current_seconds = static_cast<float>(glfwGetTime());
		float elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;

		//Paint center square
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		lgfx_setcolor(1.f, 1.f, 0.f, 1.f);
		lgfx_drawrect(screenCenter.GetX() - squareSide / 2, screenCenter.GetY() - squareSide / 2, squareSide, squareSide);
		
		//get cursor location
		glfwGetCursorPos( window, &xMousePosition, &yMousePosition);
	
		//Paint center square
		lgfx_setcolor(0.f, 1.f, 1.f, 1.f);
		lgfx_drawrect(xMousePosition - squareSide/2, yMousePosition - squareSide/2, squareSide, squareSide);

		//paint Circle
		xCirclePosition = (xMousePosition - squareSide / 2);
		yCirclePosition = (yMousePosition - squareSide / 2);
		lgfx_setcolor(1.f, 0.f, 1.f, 1.f);
		lgfx_drawoval (xCirclePosition + cos(angle)*50, yCirclePosition + sin(angle)*50, squareSide, squareSide);
		angle -= ( 32*(pi / 180)) * elapsed_seconds; //deg to rad + time
		if (angle * (180 / pi) <= -360) {
			angle = 0;
		}

		Vec2 mousePosition(xMousePosition, yMousePosition);
		float mouseScreenCenterModule = mousePosition.dist(screenCenter);
		
		//Paint on header
		std::string title = "Distancia: "
			+ stringFromNumber(mouseScreenCenterModule)
			+ " -- Angulo: "
			+ stringFromNumber(angle * (180 / pi));
		glfwSetWindowTitle(window, title.c_str());
		

		//clear buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


