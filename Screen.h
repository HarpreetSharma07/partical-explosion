#pragma once
#include<SDL.h>
#include<iostream>

class Screen
{
public:
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 400;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;


public:
	Screen();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents();
	void close();
	void clear();
};

