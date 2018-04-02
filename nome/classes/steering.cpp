#include "steering.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

SteeringOutput Seek::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput Wander::getSteering() const noexcept {
	
	Vector2f test = Vector2f(std::rand() % 100, std::rand() % 100) - Vector2f(std::rand() % 100, std::rand() % 100);
	
	SteeringOutput steering;
	steering.direction = test;
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;	
	return steering;

}


SteeringOutput Wander::getSteering(Vector2f direction) {
	
	SteeringOutput steering;
	int odds = std::rand() % 100;
	
	if (odds < 2) {		
		steering.direction = Vector2f(std::rand() % 100, std::rand() % 100);
		steering.direction = normalize(steering.direction);
		steering.direction *= _maxSpeed;
		steering.rotation = 0.0f;	
	} else {		
		steering.direction = direction;
	}
	
	return steering;

}





Wander::Wander(Entity *character, Entity *target, float maxSpeed) 
	: _character(character), _target(target), _maxSpeed(maxSpeed) {
		
	std::srand(std::time(nullptr));
	
	}


