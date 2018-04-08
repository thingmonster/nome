#include "steering.h"

SteeringOutput SeekSteering::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput FleeSteering::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput WanderSteering::getSteering() const noexcept {
	
	SteeringOutput steering;
	steering.direction = Vector2f(std::rand() % 100, std::rand() % 100) - Vector2f(std::rand() % 100, std::rand() % 100);
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;	
	return steering;

}

SteeringOutput WanderSteering::getSteering(sf::Vector2f direction) {
	
	SteeringOutput steering;
	steering.direction = Vector2f(0,0);
	
	if (direction.x == 0 && direction.y == 0) {
		// cout << "no direction " << endl;
		Vector2f newDirection = Vector2f(std::rand() % 100, std::rand() % 100) - Vector2f(std::rand() % 100, std::rand() % 100);
		steering.direction = newDirection;
	} else {
		int odds = std::rand() % 100;
		if (odds < 2) {		
			// cout << "random direction " << endl;
			Vector2f newDirection = Vector2f(std::rand() % 100, std::rand() % 100);
			steering.direction = newDirection;
		} else {	
			// cout << "same direction " << endl;
			steering.direction = direction;
		}
	}
	
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;	
	return steering;

	
}






