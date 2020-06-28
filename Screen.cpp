#include "Screen.h"

Screen::Screen(): m_window(NULL),
m_renderer(NULL),
m_texture(NULL),
m_buffer1(NULL),
m_buffer2(NULL){
	//constructor initialisation
	
}
bool Screen::init() {
	//initialize graphics mode

	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow
	("Particle Fire Explosion", // window's title
		10, 25, // coordinates on the screen, in pixels, of the window's upper left corner
		SCREEN_WIDTH, SCREEN_HEIGHT, // window's length and height in pixels  
		SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		SDL_Quit();
		return false;
	}

	//render a window , -1 for initialization , synchronised rendering
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);


	if (m_renderer == NULL)
	{
		SDL_DestroyWindow(m_window);

		SDL_Quit();

		return false;
	}

	if (m_texture == NULL)
	{
		SDL_DestroyRenderer(m_renderer);

		SDL_DestroyWindow(m_window);

		SDL_Quit();

		return false;
	}

	//datatype in SDL ,just to standardised as c++ don't have fixed 32bit int (for different devices)
	//RGBA value for a texture is 32-bit in size(each 1byte) so to store it in a block of memory
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	// turning the whole screen black by using....
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}


void Screen::update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);

}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	//checking x and y, that they are inside the screen area
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	Uint32 color = 0;


	color +=  0xFF;
	color <<= 8;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;



}

bool Screen::processEvents() {


	//events :: everything happening in one instance of a loop
	SDL_Event event;


	//SDL_PollEvent() it returns true when it finds an event
		// i.e. any kind of change
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			//like when you click cross to exit window it generates a quit event
			return false;
		}
	}
	return true;
}
void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Screen::boxBlur()
{
	//i want to copy from one buffer to another
	//so i will swap the pointers
	//so the pixels is in buffer2 and we are drawing in buffer1
	Uint32* temp = m_buffer1;
	m_buffer1=m_buffer2;
	m_buffer2 =temp;

	//iterating over all the pixels as we are going to blur out more and more
	//only new pixels will be sharp

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{

			//using bitshifting we gonna implement by defining a particular pixel
			
			//we want to add up the color values of red green and blue in each pixels
			//and then divide the result by nine
			// and then plot that result back into pixel we are intrested in setting here



			/*
			0 0 0
			0 1 0
			0 0 0
			
			*/

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <=1; row++)
			{
				for (int col = -1; col <= 1; col++)
				{
					//now we can calculate the co-ordinates of each pixel in this grid
					int currentX = x + col;
					int currentY = y + row;

					//to avoid going out of the screen
					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
						//we need to access buffer which need info of pixels
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

						Uint8 red = color >> 16;
						Uint8 green = color >>8;
						Uint8 blue = color;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;

					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);
		}
	}
}
