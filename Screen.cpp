#include "Screen.h"

Screen::Screen(): m_window(NULL),
m_renderer(NULL),
m_texture(NULL),
m_buffer(NULL) {
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
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	// turning the whole screen black by using....
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}


void Screen::update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
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

	m_buffer[(y * SCREEN_WIDTH) + x] = color;



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
	delete[] m_buffer;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}