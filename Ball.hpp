#ifndef BALL_HPP
#define BALL_HPP

#include "Vec2f.hpp"

class Ball {
	public:
	Vec2f	position;
	Vec2f	previous_position;
	Vec2f	acceleration;
	float	radius;
	float	mass;

	Ball(float x = 0.0f, float y = 0.0f, float radius = 1.0f, float mass = 1.0f);
	void	updatePosition(float dt);
};

#endif