#include "Solver.hpp"

#include <bits/stdc++.h>

void Solver::input()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			if (event.key.keysym.sym == SDLK_KP_PLUS) {
				for (int k = 0; k < 1; k++) {
					float theta = 2.0f * M_PI * distrib(mt) / 1000.0f;
					float delta = 192.0f * sqrt(distrib(mt) / 1000.0f);
					Ball b(512.0f + cosf(theta) * delta, 512.0f + sin(theta) * delta, 8.0f);
					b.acceleration = {0.0f, 1000.0f};
					balls.push_back(b);
				}
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
	qt = QuadTree<Ball>(Rectf(0.0f, 0.0f, 1024.0f, 1024.0f));
	for (Ball& ball : balls) {
		qt.Insert(ball, (Rectf){ball.position.x - ball.radius, ball.position.y - ball.radius, 2.0f * ball.radius, 2.0f * ball.radius});
		ball.color = {255, 0, 0, 255};
	}

	std::vector<Ball*> querry;
	querry.reserve(10);

	qt.Querry(querry, Rectf(mouse_pos - Vec2f(32.0f, 32.0f), Vec2f(64.0f, 64.0f)));
	for (Ball *b : querry)
		b->color = {0, 255, 0, 255};
	querry.clear();
	for (unsigned long k = 0; k < balls.size(); k++) {
		Ball& ball0 = balls.at(k);

		querry.clear();
		qt.Querry(querry, (Rectf){ball0.position.x - 2.0f * ball0.radius - 1.0f, ball0.position.y - 2.0f * ball0.radius - 1.0f, 6.0f * ball0.radius + 2.0f, 6.0f * ball0.radius + 2.0f});
		for (Ball *ball1 : querry) {
			if (&ball0 == ball1)
				continue ;
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

		if (ball0.position.x < ball0.radius + 24)
			ball0.position.x = ball0.radius + 24;
		if (ball0.position.x > 1000.0f - ball0.radius)
			ball0.position.x = 1000.0f - ball0.radius;
		if (ball0.position.y < ball0.radius + 24)
			ball0.position.y = ball0.radius + 24;
		if (ball0.position.y > 1000.0f - ball0.radius)
			ball0.position.y = 1000.0f - ball0.radius;

		// Vec2f to_obj = ball0.position - Vec2f(512.0f, 512.0f);
		// float dist = to_obj.getNorm();
		// if (dist > 512.0f - ball0.radius) {
		// 	Vec2f n = to_obj / dist;
		// 	ball0.position = Vec2f(512.0f, 512.0f) + n * (512.0f - ball0.radius);
		// }
	}
	for (unsigned long k = 0; k < balls.size(); k++)
		balls[k].updatePosition(dt);
}

void Solver::render()
{
	drawer.SetColor(255, 255, 255);
	drawer.Clear();
	drawer.SetColor(255, 192, 192);
	qt.Draw(drawer);
	drawer.SetColor(32, 32, 192);
	for (Ball& ball : balls) {
		drawer.SetColor(ball.color.r, ball.color.g, ball.color.b, ball.color.a);
		drawer.DrawThinCircle((int)ball.position.x, (int)ball.position.y, (int)ball.radius);
	}
	drawer.SetColor(0, 255, 0);
	drawer.DrawRect(mouse_pos.x - 32, mouse_pos.y - 32, 64, 64);
	drawer.SetColor(32, 32, 32);
	drawer.Write("dt:" + std::to_string(dt) + "", 32, 32);
	drawer.Write("fps:" + std::to_string(1.0f / dt) + "", 32, 48);
	drawer.Write("count:" + std::to_string(balls.size()), 32, 64);
	//drawer.Present();
}

Solver::Solver() : 
	qt(Rectf(0.0f, 0.0f, 1024.0f, 1024.0f)),
	mt(std::random_device()()),
	distrib(0, 1000)
{
	previous_tp = std::chrono::steady_clock::now();
	balls.reserve(10000);
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
		//logic();
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
