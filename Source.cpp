#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace std;
int main(int argc, char* argv[])
{
	//creating object
	Screen screen;
	if (screen.init() == false)
	{
		cout << "error\n";
	}
	

	//gameloop
	while (true) {

		//SDL_GetTicks()->>
		//it returns the number of millisec since the program starts
		//sin()->> it return values between -1 to 1
		// unsigned char -> is used to get a value less than 255
		//0.001 is multiplied with *elapsed* to return smooth values by sin function
		//+1 ->> is added to get values between range(0-2)
		
		
		int elapsed = SDL_GetTicks();
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.003)) * 128);



		for (int y = 0; y < Screen::SCREEN_HEIGHT;y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x,y,red,green,blue);
			}
		}
		screen.update();
		if (screen.processEvents() == false)
		{
			break;
		}
		
	}
	  
	screen.close();
	return 0;
}