#include "Rectf.hpp"

Rectf::Rectf(const Vec2f &pos, const Vec2f &size) {
	this->pos = pos;
	this->size = size;
}

Rectf::Rectf(float x, float y, float w, float h) {
	pos = {x, y};
	size = {w, h};
}

bool Rectf::Instersects(const Rectf &rect) const {
	return (
		pos.x <= rect.pos.x + rect.size.x &&
		pos.x + size.x >= rect.pos.x &&
		pos.y <= rect.pos.y + rect.size.y &&
		pos.y + size.y >= rect.pos.y
	);
}

bool Rectf::Contains(const Rectf &rect) const {
	return (
		pos.x < rect.pos.x &&
		pos.x + size.x > rect.pos.x + rect.size.x &&
		pos.y < rect.pos.y &&
		pos.y + size.y > rect.pos.y + rect.size.y
	);
}

bool Rectf::Contains(const Vec2f &point) const {
	return (
		pos.y < point.y &&
		pos.y + size.y > point.y &&
		pos.y < point.y &&
		pos.y + size.y > point.y
	);
}
