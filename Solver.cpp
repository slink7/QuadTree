#include "Solver.hpp"

#include <bits/stdc++.h>

void Solver::input()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			if (event.key.keysym.sym == SDLK_KP_PLUS) {
				Ball b(400.0f + (distrib(mt) / 100.0f), 255.0f, 2.0f + (distrib(mt) / 200.0f));
				//b.acceleration = {distrib(mt) - 500.0f, distrib(mt) - 500.0f};
				balls.push_back(b);
			}
		}
	}
}

void Solver::logic()
{
	for (unsigned long k = 0; k < balls.size(); k++) {
		Ball& ball0 = balls.at(k);
		ball0.acceleration = {0.0f, 0.0f};
		for (unsigned long l = k + 1; l < balls.size(); l++) {
			Ball& ball1 = balls.at(l);
			Vec2f	dp = ball0.position - ball1.position;
			float	dist = dp.getNorm();
			float	min_dist = ball0.radius + ball1.radius;
			if (dist < min_dist) {
				const Vec2f n = dp / dist;
				const float delta = min_dist - dist;
				ball0.position += n * (ball0.radius / min_dist) * delta;
				ball1.position -= n * (ball0.radius / min_dist) * delta;
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
	drawer.SetColor(32, 32, 192);
	for (Ball& ball : balls) {
		drawer.DrawThinCircle((int)ball.position.x, (int)ball.position.y, (int)ball.radius);
	}
	drawer.Write("dt:" + std::to_string(dt) + "", 32, 32);
	drawer.Write("fps:" + std::to_string(1.0f / dt) + "", 32, 48);
	drawer.Write("count:" + std::to_string(balls.size()), 32, 64);
	drawer.Present();
}

Solver::Solver()
	: mt(std::random_device()()),
	distrib(0, 1000)
{
	previous_tp = std::chrono::steady_clock::now();
}

void Solver::run()
{
	while (!exit) {
		dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_tp).count() / 1000000.0f;
		previous_tp = std::chrono::steady_clock::now();
		input();
		logic();
		render();
		if (dt < 0.016) {
			dt_correction = 16 - (dt * 1000);
			SDL_Delay(dt_correction);
		}
	}
}
