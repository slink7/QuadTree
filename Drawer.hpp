#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <SDL2/SDL.h>

class Drawer {

public:
	Drawer(const char *title = "Title", int width = 256, int height = 256);
	~Drawer();

private:
	SDL_Window		*window;
	SDL_Renderer	*renderer;

};

#endif