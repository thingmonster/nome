#include "steering.h"

SteeringOutput SeekSteering::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.rotation = vector2degrees(steering.direction);
	steering.direction *= _maxSpeed;
	return steering;
}

SteeringOutput FleeSteering::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.rotation = vector2degrees(steering.direction);
	steering.direction *= _maxSpeed;
	return steering;
}


WanderSteering::WanderSteering(Entity *character, Entity *target, float maxSpeed)
	: _character(character), _target(target), _maxSpeed(maxSpeed) {
	srand( time( NULL ) );
}


SteeringOutput WanderSteering::getSteering() const noexcept {
	
	// assign a random direction to steering
	
	SteeringOutput steering;
	steering.direction = Vector2f((std::rand() % 100) - 50, (std::rand() % 100) - 50);
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = vector2degrees(steering.direction);
	return steering;

}

SteeringOutput WanderSteering::getSteering(sf::Vector2f direction) {
	
	SteeringOutput steering;
	steering.direction = Vector2f(0,0);
	
	// current direction not set, generate one at random
	if (direction.x == 0 && direction.y == 0) {
		Vector2f newDirection = Vector2f(std::rand() % 100, std::rand() % 100) - Vector2f(std::rand() % 100, std::rand() % 100);
		steering.direction = newDirection;
	} 
	
	// otherwise 2% chance of changing to a new random direction
	else {
		int odds = std::rand() % 100;
		if (odds < 2) {	
			Vector2f newDirection = Vector2f((std::rand() % 100) - 50, (std::rand() % 100) - 50);
			steering.direction = newDirection;
		} else {	
			steering.direction = direction;
		}
	}
	
	steering.direction = normalize(steering.direction);
	steering.rotation = vector2degrees(steering.direction);
	steering.direction *= _maxSpeed;
	return steering;

	
}






