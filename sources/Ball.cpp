#include "Ball.hpp"

Ball::Ball(float x, float y, float radius, float mass) {
	position = Vec2f(x, y);
	previous_position = position;
	this->radius = radius;
	this->mass = mass;

	acceleration = Vec2f(0.0f, 0.0f);
}

void Ball::updatePosition(float dt) {
	const Vec2f vel = position - previous_position;
	previous_position = position;
	position += vel + acceleration * dt * dt;
}
