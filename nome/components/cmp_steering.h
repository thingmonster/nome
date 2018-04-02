#pragma once
#include <iostream>
#include "cmp_movement.h"
#include "../classes/steering.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class SteeringComponent : public MovementComponent {
	
	private:
		Seek _seek;
		Flee _flee;
		Wander _wander;
		Entity *_player;
		Vector2f _direction;
		
	public:
		SteeringComponent() = delete;
		explicit SteeringComponent(Entity *p, Entity *player);		
		void update(double dt) override;
	
	
};