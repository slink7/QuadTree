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

bool QuadTree::IsIn(const Vec2f &A, const Vec2f &pos, float size)
{
	// std::cout << A << " " << pos << " " << size << "\n";
	// std::cout << ((A.x > (pos.x - size / 2.0f)) &&
	// 	(A.x < (pos.x + size / 2.0f)) &&
	// 	(A.y > (pos.y - size / 2.0f)) &&
	// 	(A.y < (pos.y + size / 2.0f))) << "\n";
	return (
		(A.x > (pos.x - size / 2.0f)) &&
		(A.x < (pos.x + size / 2.0f)) &&
		(A.y > (pos.y - size / 2.0f)) &&
		(A.y < (pos.y + size / 2.0f))
	);
}

bool QuadTree::Intersect(const Vec2f &pos, float s)
{
	return (
		((pos.x - s / 2.0f) <= (position.x + size / 2.0f)) &&
		((pos.x + s / 2.0f) >= (position.x - size / 2.0f)) &&
		((pos.y - s / 2.0f) <= (position.y + size / 2.0f)) &&
		((pos.y + s / 2.0f) >= (position.y - size / 2.0f))
	);
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



void QuadTree::Querry(std::vector<Ball*>& out, const Vec2f &pos, float size)
{
	if (!Intersect(pos, size))
		return ;
	if (subdivided) {
		for (int k = 0; k < 4; k++)
			children[k]->Querry(out, pos, size);
		return ;
	}
	for (Ball *b : values)
		if (IsIn(b->position, pos, size))
			out.push_back(b);
}
