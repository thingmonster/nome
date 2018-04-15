#pragma once
#include <iostream>
#include "cmp_movement.h"
#include "cmp_state_machine.h"
#include "../classes/steering.h"
#include <SFML/Graphics.hpp>

/*

this class is not used

*/


using namespace sf;
using namespace std;

class SteeringComponent : public MovementComponent {
	
	private:
		SeekSteering _seek;
		FleeSteering _flee;
		WanderSteering _wander;
		Entity *_player;
		Vector2f _direction;
		
	public:
		SteeringComponent() = delete;
		explicit SteeringComponent(Entity *p, Entity *player);		
		void update(double dt) override;
	
	
};