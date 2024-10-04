#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Drawer {

public:
	Drawer(const char *title = "Title", int width = 1024, int height = 1024);
	~Drawer();

	void	SetColor(int r, int g, int b, int a = 255) const;
	void	Clear() const;
	void	DrawRect(int x, int y, int w, int h) const;
	void	FillRect(int x, int y, int w, int h) const;
	void	DrawThinLine(int x0, int y0, int x1, int y1) const;
	void	DrawLine(int x0, int y0, int x1, int y1, int thickness = 1) const;
	void	DrawThinCircle(int x, int y, int radius) const;
	void	FillCircle(int x, int y, int radius) const;
	void	DrawPixel(int x, int y) const;
	void	Write(const std::string& str, int x, int y) const;
	void	Present() const;

private:
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
};

#endif