#include "QuadTree.hpp"

#include <iostream>

QuadTree::QuadTree(const Vec2f &pos, float size, int max_values)
{
	position = pos;
	this->size = size;
	this->max_values = max_values;
	subdivided = false;
	values.reserve(max_values);
}

void QuadTree::Insert(Ball &ball)
{
	if (!subdivided && (int) values.size() < max_values) {
		values.push_back(&ball);
		return ;
	}
	if (!subdivided)
		Subdivide();
	int index = (ball.position.x > position.x) + 2 * (ball.position.y > position.y);
	children[index]->Insert(ball);
}

void QuadTree::Subdivide()
{
	float hs = size / 2.0f;
	children[0] = std::make_unique<QuadTree>((Vec2f){position.x - hs / 2, position.y - hs / 2}, hs, max_values);
	children[1] = std::make_unique<QuadTree>((Vec2f){position.x + hs / 2, position.y - hs / 2}, hs, max_values);
	children[2] = std::make_unique<QuadTree>((Vec2f){position.x - hs / 2, position.y + hs / 2}, hs, max_values);
	children[3] = std::make_unique<QuadTree>((Vec2f){position.x + hs / 2, position.y + hs / 2}, hs, max_values);
	subdivided = true;
	for (int k = 0; k < max_values; k++) {
		int index = (values[k]->position.x > position.x) + 2 * (values[k]->position.y > position.y);
		children[index]->Insert(*values[k]);
	}
	values.clear();
}
