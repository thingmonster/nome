
#include "cmp_movement.h"

/*

mostly drawn directly from examples in the workbook, but move method
checks ahead for valid position and returns a boolean so alternative
action can be taken if the move does not succeed

*/

using namespace sf;

void MovementComponent::update(double dt) {
}

MovementComponent::MovementComponent(Entity* p) : _speed(ls::getTileSize()), Component(p) {}

bool MovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileFromScreenCoords(pos) != LevelSystem::WALL);
}

bool MovementComponent::move(const sf::Vector2f& p) {
	
	// look ahead just a little bit so we don't get stuck in walls
	auto pp = _parent->getPosition() + p;
	if (validMove(Vector2f(pp.x + (ls::getTileSize() / 400 * _direction.x), pp.y + (ls::getTileSize() / 400 * _direction.y)))) {
		_parent->setPosition(pp);
		return true;
	} else {
		return false;
	}
}

bool MovementComponent::move(float x, float y) {
	if (move(Vector2f(x, y))) {
		return true;
	} else {
		return false;
	}
}

float MovementComponent::getSpeed() const {
	return _speed;
}

void MovementComponent::setSpeed(float speed) {
	_speed = speed;
}

sf::Vector2f MovementComponent::getDirection() const {
	return _direction;
}

void MovementComponent::setDirection(sf::Vector2f direction) {
	_direction = direction;
}