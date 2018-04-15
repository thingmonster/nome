#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "engine.h"

/*

this file contains the definitions for the 
SteeringOutput struct, the SteeringBehaviour 
class and all the individual steering classes

*/



struct SteeringOutput {
	sf::Vector2f direction;
	float rotation;
};


class SteeringBehaviour {
	
	public:
		virtual ~SteeringBehaviour() = default;
		virtual SteeringOutput getSteering() const noexcept = 0;
		
};

class SeekSteering : public SteeringBehaviour {
	
	private:
		Entity* _character;
		Entity* _target;
		float _maxSpeed;
		
	public:
		SeekSteering() = delete;
		SeekSteering(Entity *character, Entity *target, float maxSpeed) 
			: _character(character), _target(target), _maxSpeed(maxSpeed) {}
		SteeringOutput getSteering() const noexcept;
};
		

class FleeSteering : public SteeringBehaviour {
	
	private:
		Entity* _character;
		Entity* _target;
		float _maxSpeed;
		
	public:
		FleeSteering() = delete;
		FleeSteering(Entity *character, Entity *target, float maxSpeed) 
			: _character(character), _target(target), _maxSpeed(maxSpeed) {}
		SteeringOutput getSteering() const noexcept;
};
		
class WanderSteering : public SteeringBehaviour {
	
	private:
		Entity* _character;
		Entity* _target;
		float _maxSpeed;
		
	public:
		WanderSteering() = delete;
		WanderSteering(Entity *character, Entity *target, float maxSpeed)
			: _character(character), _target(target), _maxSpeed(maxSpeed) {}
		SteeringOutput getSteering() const noexcept;
		SteeringOutput getSteering(sf::Vector2f direction);
};
		
