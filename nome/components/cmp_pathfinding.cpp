
#include "cmp_pathfinding.h"


using namespace std;
using namespace sf;

void PathfindingComponent::update(double dt) {
	_elapsed += dt;
	if (_elapsed >= 1.1) {
		_elapsed = 0.0;
		if (_index < _path.size()) {
			float new_x = _path[_index].x * ls::getTileSize() + (ls::getTileSize() / 2);
			float new_y = _path[_index].y * ls::getTileSize() + (ls::getTileSize() / 2);
			_parent->setPosition(Vector2f(new_x, new_y));
			++_index;
		}
	}
}

void PathfindingComponent::render() {
	
}

PathfindingComponent::PathfindingComponent(Entity* p) : Component(p) {}

void PathfindingComponent::setPath(std::vector<sf::Vector2i>& path) {
	_index = 0;
	_path = path;
}



