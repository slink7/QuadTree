#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "QuadTree.hpp"

class Drawer {

public:
	Drawer(const char *title = "Title", int width = 512, int height = 512);
	~Drawer();

	void	SetColor(int r, int g, int b, int a = 255);
	void	Clear();
	void	FillRect(int x, int y, int w, int h);
	void	DrawThinLine(int x0, int y0, int x1, int y1);
	void	DrawLine(int x0, int y0, int x1, int y1, int thickness = 1);
	void	DrawThinCircle(int x, int y, int radius);
	void	FillCircle(int x, int y, int radius);
	void	DrawPixel(int x, int y);
	void	DrawQuadTree(QuadTree& qt);
	void	Write(const std::string& str, int x, int y);
	void	Present();

private:
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
};

#endif