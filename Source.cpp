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
	

	bool quit = false;

	






	

	//gameloop
	while (!quit) {

		for (int y = 0; y < Screen::SCREEN_HEIGHT;y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x,y,128,0,255);
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