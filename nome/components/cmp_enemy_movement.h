#pragma once
#include <iostream>
#include "cmp_actor_movement.h"
#include "../classes/steering.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class EnemyMovementComponent : public ActorMovementComponent {
	
	private:
		Seek _seek;
		Flee _flee;
		Wander _wander;
		Entity *_player;
		Vector2f _direction;
		
	public:
		EnemyMovementComponent() = delete;
		explicit EnemyMovementComponent(Entity *p, Entity *player);		
		void update(double dt) override;
	
	
};