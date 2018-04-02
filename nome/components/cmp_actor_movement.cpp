
#include "cmp_actor_movement.h"


using namespace sf;

void ActorMovementComponent::update(double dt) {
}

ActorMovementComponent::ActorMovementComponent(Entity* p) : _speed(200.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	
	
	
	return (LevelSystem::getTileFromScreenCoords(pos) != LevelSystem::WALL);
}

bool ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
		return true;
	} else {
		return false;
	}
}

bool ActorMovementComponent::move(float x, float y) {
	if (move(Vector2f(x, y))) {
		return true;
	} else {
		return false;
	}
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}