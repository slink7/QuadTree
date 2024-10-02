#ifndef QUADTREE_H
#define QUADTREE_H

#include <array>
#include <vector>
#include <memory>

#include "Ball.hpp"

class QuadTree {
public:
	std::array<std::unique_ptr<QuadTree>, 4>	children;
	std::vector<Ball*>	values;
	Vec2f	position;
	float	size;
	bool	subdivided;
	int		max_values;

	QuadTree() = default;
	QuadTree(const Vec2f& pos, float size, int max_values = 4);

	void Insert(Ball& ball);
	void Subdivide();
};


#endif