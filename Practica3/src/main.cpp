
#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <stdlib.h>
#include <time.h> 
#include <Font.h>


using namespace std;

int windowWidth = 1020, windowHeight = 720;

int main() {

	if (glfwInit() == GLFW_TRUE)
	{
		static float previous_seconds = static_cast<float>(glfwGetTime());
		float current_seconds = 0;
		float elapsed_seconds = 0;
		std::vector<Font*> vFonts;
		
		const char* text = "Hello World!";
		
		const char* sFilePath[]{
			"data/SFSlapstickComic.ttf",
			"data/Angeline Vintage_Demo.ttf",
			"data/BORUDE FREE.ttf",
			"data/Lasttosleep-Regular.ttf",
			"data/Los Diablos.ttf",
			"data/Roman Morrissey DEMO.ttf",
			"data/Samureix-Regular.ttf",
			"data/Shadow Brush.ttf",
			"data/Valentine Monster.ttf",
		};

		GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "The text is the word", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		lgfx_setup2d( windowWidth, windowHeight);

		while (!glfwWindowShouldClose(window))
		{
			current_seconds = static_cast<float>(glfwGetTime());
			elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;
			
			lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

			if (0 == (rand() % 101))
			{
				Font* newFont;
				int index = rand() % 9;
				newFont = newFont->load(sFilePath[index], 32.f);
				newFont->fX = windowWidth - newFont->getTextSize(text).GetX();
				newFont->fY = (rand() % windowHeight);
				newFont->fVelocity =  (rand() % 200 + 20);

				vFonts.push_back(newFont);
			}
			
			for (std::vector<Font*>::iterator element = vFonts.begin(); element != vFonts.end(); )
			//for (Font* element : vFonts)
			{
				
				if((*element)->fX > 0)
				{
					(*element)->fX -= (*element)->fVelocity * elapsed_seconds;
					lgfx_setcolor((*element)->colorX, (*element)->colorY, (*element)->colorZ, 1.f);
					lgfx_setblend(BLEND_ALPHA);

					(*element)->draw( text, Vec2((*element)->fX, (*element)->fY) );

					++element;
				}
				else
				{
					(*element)->destroyFont(Vec2((*element)->fX, (*element)->fY));
					element = vFonts.erase(element);
				}
			}

			//Borrar buffer
			glfwSwapBuffers(window);
			glfwPollEvents();

		}

		glfwTerminate();

	}

    return 0;
}
