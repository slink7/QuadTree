#ifndef VEC2F_HPP
#define VEC2F_HPP

#include <cmath>
#include <ostream>

struct Vec2f {
	float x, y;

	Vec2f();
	Vec2f(float x, float y);

	Vec2f&	operator=(const Vec2f& other);
	Vec2f&	operator+=(const Vec2f& other);
	Vec2f&	operator-=(const Vec2f& other);
	Vec2f&	operator*=(const float& other);
	Vec2f&	operator/=(const float& other);

	Vec2f	operator+(const Vec2f& other) const;
	Vec2f	operator-(const Vec2f& other) const;
	Vec2f	operator*(const float& other) const;
	Vec2f	operator/(const float& other) const;

	float	getNorm() const;
	float	getSquaredNorm() const;
	float	dot(const Vec2f& other) const;
};

std::ostream	&operator<<(std::ostream &stream, const Vec2f& vec);

#endif