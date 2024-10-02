#include "Solver.hpp"

#include <bits/stdc++.h>

void Solver::input()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			if (event.key.keysym.sym == SDLK_KP_PLUS) {
				float theta = 2.0f * M_PI * distrib(mt) / 1000.0f;
				float delta = 192.0f * sqrt(distrib(mt) / 1000.0f);
				Ball b(256.0f + cosf(theta) * delta, 256.0f + sin(theta) * delta, 3.0f);
				//b.acceleration = {distrib(mt) - 500.0f, distrib(mt) - 500.0f};
				balls.push_back(b);
			}
		}
		if (event.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			mouse_pos.x = x;
			mouse_pos.y = y;
		}
	}
}

void Solver::logic()
{
	qt = QuadTree((Vec2f){256.0f, 256.0f}, 512.0f, 8);
	for (Ball& ball : balls) {
		qt.Insert(ball);
	}

	for (unsigned long k = 0; k < balls.size(); k++) {
		Ball& ball0 = balls.at(k);
		ball0.acceleration = {0.0f, 0.0f};
		std::vector<Ball*> querry;
		querry.reserve(10);
		qt.Querry(querry, ball0.position, 7.0f);
		for (Ball *ball1 : querry) {
			if (&ball0 == ball1)
				break ;
			Vec2f	dp = ball0.position - ball1->position;
			float	dist = dp.getNorm();
			float	min_dist = ball0.radius + ball1->radius;
			if (dist < min_dist) {
				const Vec2f n = dp / dist;
				const float delta = min_dist - dist;
				ball0.position += n * (ball0.radius / min_dist) * delta;
				ball1->position -= n * (ball0.radius / min_dist) * delta;
			}
		}

		Vec2f to_obj = ball0.position - Vec2f(256.0f, 256.0f);
		float dist = to_obj.getNorm();
		if (dist > 256.0f - ball0.radius) {
			Vec2f n = to_obj / dist;
			ball0.position = Vec2f(256.0f, 256.0f) + n * (256.0f - ball0.radius);
		}
		ball0.updatePosition(dt);
	}
}

void Solver::render()
{
	drawer.SetColor(255, 255, 255);
	drawer.Clear();
	drawer.SetColor(192, 32, 32);
	drawer.DrawQuadTree(qt);
	drawer.SetColor(32, 32, 192);
	for (Ball& ball : balls) {
		drawer.DrawThinCircle((int)ball.position.x, (int)ball.position.y, (int)ball.radius);
	}
	drawer.SetColor(0, 255, 0);
	drawer.DrawRect(mouse_pos.x - 64, mouse_pos.y - 64, 128, 128);
	drawer.SetColor(32, 32, 32);
	drawer.Write("dt:" + std::to_string(dt) + "", 32, 32);
	drawer.Write("fps:" + std::to_string(1.0f / dt) + "", 32, 48);
	drawer.Write("count:" + std::to_string(balls.size()), 32, 64);
	drawer.Present();
}

Solver::Solver() : 
	qt((Vec2f){256.0f, 256.0f}, 512.0f, 8),
	mt(std::random_device()()),
	distrib(0, 1000)
{
	previous_tp = std::chrono::steady_clock::now();
	balls.reserve(3000);
}

void Solver::run()
{
	std::chrono::steady_clock::time_point A;

	while (!exit) {
		dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_tp).count() / 1000000.0f;
		previous_tp = std::chrono::steady_clock::now();

		A = std::chrono::steady_clock::now();
		input();
		float dt_input = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - A).count() / 1000000.0f;

		A = std::chrono::steady_clock::now();
		logic();
		float dt_logic = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - A).count() / 1000000.0f;

		A = std::chrono::steady_clock::now();
		render();
		float dt_render = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - A).count() / 1000000.0f;

		float sum = dt_render + dt_logic + dt_input;
		drawer.SetColor(0, 255, 0);
		drawer.FillRect(32, 88, 128 * (dt_input / sum), 8);
		drawer.SetColor(0, 0, 255);
		drawer.FillRect(32 + 128 * (dt_input / sum), 88, 128 * (dt_logic / sum), 8);
		drawer.SetColor(255, 0, 0);
		drawer.FillRect(32 + 128 * (dt_input / sum) + 128 * (dt_logic / sum), 88, 128 * (dt_render / sum), 8);
		drawer.Present();
		if (dt < 0.016) {
			dt_correction = 16 - (dt * 1000);
			SDL_Delay(dt_correction);
		}
	}
}
