#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "Swarm.h"

using namespace std;
int main(int argc, char* argv[])
{
	//seed random
	srand(time(NULL));


	//creating object
	Screen screen;
	if (screen.init() == false)
	{
		cout << "error\n";
	}
	
	Swarm swarm;

	//gameloop
	while (true) {


		//SDL_GetTicks()->>
		//it returns the number of millisec since the program starts
		int elapsed = SDL_GetTicks();

		//updating positions of particles  
		swarm.update(elapsed);



		//sin()->> it return values between -1 to 1
		// unsigned char -> is used to get a value less than 255
		//0.001 is multiplied with *elapsed* to return smooth values by sin function
		//+1 ->> is added to get values between range(0-2)

		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.003)) * 128);








		//loop through all particles
		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];
			//position of a particle in x -axis and y-xis
			//from 0 to screen width and height respect..
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y  * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;


			screen.setPixel(x, y, red, green, blue);
		}

		//to blur the pixels
		screen.boxBlur();


		/*

		for (int y = 0; y < Screen::SCREEN_HEIGHT;y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
			}
		}*/

		//drawing the screen
		screen.update();
		if (screen.processEvents() == false)
		{
			break;
		}
		
	}
	  
	screen.close();
	return 0;
}