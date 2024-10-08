#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2f.hpp"

struct Rectf {
	Vec2f	pos;
	Vec2f	size;

	Rectf() = default;
	Rectf(const Vec2f& pos, const Vec2f& size);
	Rectf(float x, float y, float w, float h);

	bool	Instersects(const Rectf& rect) const;
	bool	Contains(const Rectf& rect) const;
	bool	Contains(const Vec2f& point) const;
};

#endif