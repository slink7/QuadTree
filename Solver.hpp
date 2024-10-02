#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <random>
#include <chrono>

#include "Vec2f.hpp"
#include "Ball.hpp"
#include "Drawer.hpp"
#include "QuadTree.hpp"

class Solver {

	Drawer				drawer;
	SDL_Event			event;
	bool				exit;
	std::vector<Ball>	balls;
	float				dt;
	int					dt_correction;
	QuadTree			qt;
	Vec2f				mouse_pos;

	std::random_device	random_dev;
	std::mt19937		mt;
	std::uniform_int_distribution<std::mt19937::result_type> distrib;

	std::chrono::steady_clock::time_point previous_tp;

	void	input();
	void	logic();
	void	render();

public:
	Solver();
	void	run();
};

#endif