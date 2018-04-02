#pragma once
#include <iostream>
#include "cmp_actor_movement.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class EnemyMovementComponent : public ActorMovementComponent {
	
	private:
		int _direction;
		
	public:
		EnemyMovementComponent() = delete;
		explicit EnemyMovementComponent(Entity *p);
		void update(double dt) override;
	
};