#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <array>
#include <vector>
#include <list>
#include <memory>

#include "Rectf.hpp"
#include "Drawer.hpp"

template <typename T>
class QuadTree {

private:

	class QuadTreeNode {
		static int MAX_DEPTH;

		Rectf	area;

		std::array<std::unique_ptr<QuadTreeNode>, 4>	children;

		std::vector<std::pair<Rectf, T*>>	items;

		int depth;

	public:
		QuadTreeNode() = default;
		QuadTreeNode(const Rectf& area, int depth = 0);

		const Rectf	&GetArea() const;

		void	Insert(T& value, const Rectf& varea);
		void	Querry(std::vector<T*>& out, const Rectf& area);
		void	Draw(const Drawer& d);
	};
 
	std::list<T>	items;
	QuadTreeNode	root;

	int		max_values;

public:

	QuadTree() = default;
	QuadTree(const Rectf& area);

	void	Insert(T& t, const Rectf& area);
	void	Querry(std::vector<T*>& out, const Rectf& area);
	void	Draw(const Drawer& d);
};

template <typename T>
int QuadTree<T>::QuadTreeNode::MAX_DEPTH = 8;

template <typename T>
QuadTree<T>::QuadTreeNode::QuadTreeNode(const Rectf &area, int depth) :
	area(area),
	depth(depth)
{}

template <typename T>
const Rectf &QuadTree<T>::QuadTreeNode::GetArea() const {
	return (area);
}

template <typename T>
void QuadTree<T>::QuadTreeNode::Insert(T &value, const Rectf &varea)
{
	for (int k = 0; k < 4; k++) {
		if (depth + 1 >= MAX_DEPTH)
			break ;
		if (!children[k]) {
			Rectf carea = {area.pos.x + (k % 2) * area.size.x / 2.0f, area.pos.y + (k / 2) * area.size.y / 2.0f, area.size.x / 2.0f, area.size.y / 2.0f};
			children[k] = std::make_unique<QuadTreeNode>(carea, depth + 1);
		}
		if (!children[k]->GetArea().Contains(varea))
			continue ;
		children[k]->Insert(value, varea);
		return ;
	}
	items.push_back(std::pair<Rectf, T*>(varea, &value));
}

template <typename T>
void QuadTree<T>::QuadTreeNode::Querry(std::vector<T *> &out, const Rectf &querry)
{
	if (!area.Instersects(querry))
		return ;
	for (int k = 0; k < 4; k++) {
		if (children[k])
			children[k]->Querry(out, querry);
	}
	for (std::pair<Rectf, T*> &pair : items) {
		if (querry.Contains(pair.first))
			out.push_back(pair.second);
	}
}

template <typename T>
void QuadTree<T>::QuadTreeNode::Draw(const Drawer &d)
{
	d.DrawRect(area.pos.x, area.pos.y, area.size.x, area.size.y);
	for (int k = 0; k < 4; k++)
		if (children[k] && children[k]->items.size() > 0)
			children[k]->Draw(d);
}

template <typename T>
QuadTree<T>::QuadTree(const Rectf &area) :
	root(area)
{}

template <typename T>
void QuadTree<T>::Insert(T &t, const Rectf &area) {
	items.push_back(t);
	root.Insert(t, area);
}

template <typename T>
void QuadTree<T>::Querry(std::vector<T *> &out, const Rectf& area) {
	root.Querry(out, area);
}

template <typename T>
void QuadTree<T>::Draw(const Drawer &d)
{
	root.Draw(d);
}

#endif