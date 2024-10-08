#include "Vec2f.hpp"

Vec2f::Vec2f()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2f::Vec2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2f &Vec2f::operator=(const Vec2f &other)
{
	x = other.x;
	y = other.y;
	return (*this);
}

Vec2f &Vec2f::operator+=(const Vec2f &other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

Vec2f &Vec2f::operator-=(const Vec2f &other) {
	x -= other.x;
	y -= other.y;
	return (*this);
}

Vec2f &Vec2f::operator*=(const float &other) {
	x *= other;
	y *= other;
	return (*this);
}

Vec2f &Vec2f::operator/=(const float &other) {
	x /= other;
	y /= other;
	return (*this);
}

Vec2f Vec2f::operator+(const Vec2f &other) const
{
	return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f &other) const
{
	return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(const float &other) const
{
	return Vec2f(x * other, y * other);
}

Vec2f Vec2f::operator/(const float &other) const
{
	return Vec2f(x / other, y / other);
}

float Vec2f::getNorm() const
{
	return (sqrtf(x * x + y * y));
}

float Vec2f::getSquaredNorm() const
{
	return (x * x + y * y);
}

float Vec2f::dot(const Vec2f &other) const
{
	return (x * other.x + y * other.y);
}

std::ostream &operator<<(std::ostream &stream, const Vec2f& vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return (stream);
}