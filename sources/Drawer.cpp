#include "Drawer.hpp"

Drawer::Drawer(const char *title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
	renderer = SDL_CreateRenderer(window, -1, 0);
	font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
}

Drawer::~Drawer()
{
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void Drawer::SetColor(int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Drawer::Clear() const
{
	SDL_RenderClear(renderer);
}

void Drawer::DrawRect(int x, int y, int w, int h) const
{
	SDL_Rect	rect = {x, y, w, h};

	SDL_RenderDrawRect(renderer, &rect);
}

void Drawer::FillRect(int x, int y, int w, int h) const
{
	SDL_Rect	rect = {x, y, w, h};

	SDL_RenderFillRect(renderer, &rect);
}

void Drawer::DrawThinLine(int x0, int y0, int x1, int y1) const
{
	int dx = abs(x1 - x0);
	int	sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int	sy = y0 < y1 ? 1 : -1;
	int	error = dx + dy;
	int	e2;

	while (true) {
		SDL_RenderDrawPoint(renderer, x0, y0);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * error;
		if (e2 >= dy) {
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			error += dx;
			y0 += sy;
		}
	}
}

void Drawer::DrawLine(int x0, int y0, int x1, int y1, int thickness) const
{
	int dx = abs(x1 - x0);
	int	sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int	sy = y0 < y1 ? 1 : -1;
	int	error = dx + dy;
	int	e2;
	SDL_Rect rect = {x0, y0, thickness, thickness};

	while (true) {
		SDL_RenderFillRect(renderer, &rect);
		if (rect.x == x1 && rect.y == y1)
			break ;
		e2 = 2 * error;
		if (e2 >= dy) {
			error += dy;
			rect.x += sx;
		}
		if (e2 <= dx) {
			error += dx;
			rect.y += sy;
		}
	}
}

void Drawer::DrawThinCircle(int x, int y, int radius) const
{
	int cx = 0;
	int cy = -radius;
	int p = -radius;

	while (cx < -cy) {
		if (p > 0) {
			cy += 1;
			p += 2 * (cx + cy) + 1;
		} else {
			p += 2 * cx + 1;
		}
		SDL_RenderDrawPoint(renderer, x + cx, y + cy);
		SDL_RenderDrawPoint(renderer, x - cx, y + cy);
		SDL_RenderDrawPoint(renderer, x + cx, y - cy);
		SDL_RenderDrawPoint(renderer, x - cx, y - cy);
		SDL_RenderDrawPoint(renderer, x + cy, y + cx);
		SDL_RenderDrawPoint(renderer, x - cy, y + cx);
		SDL_RenderDrawPoint(renderer, x + cy, y - cx);
		SDL_RenderDrawPoint(renderer, x - cy, y - cx);
		cx += 1;
	}
}

void Drawer::FillCircle(int x, int y, int radius) const
{
	int cx = 0;
	int cy = -radius;
	int p = -radius;

	while (cx < -cy) {
		if (p > 0) {
			cy += 1;
			p += 2 * (cx + cy) + 1;
		} else {
			p += 2 * cx + 1;
		}
		DrawThinLine(x + cx, y + cy, x + cx, y - cy);
		DrawThinLine(x - cx, y + cy, x - cx, y - cy);
		DrawThinLine(x + cy, y + cx, x + cy, y - cx);
		DrawThinLine(x - cy, y + cx, x - cy, y - cx);
		cx += 1;
	}
}

void Drawer::DrawPixel(int x, int y) const
{
	SDL_RenderDrawPoint(renderer, x, y);
}

void Drawer::Write(const std::string& str, int x, int y) const
{
	SDL_Surface *surf = TTF_RenderText_Solid(font, str.c_str(), {0, 0, 0, 0});
	SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_Rect dst = {x, y, 0, 0};
	SDL_QueryTexture(text, 0, 0, &dst.w, &dst.h);
	SDL_RenderCopyEx(renderer, text, 0, &dst, 0.0, 0, SDL_FLIP_NONE);
	SDL_DestroyTexture(text);
}

void Drawer::Present() const
{
	SDL_RenderPresent(renderer);
}
