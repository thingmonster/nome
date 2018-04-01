#pragma once
#include "cmp_actor_movement.h"

class PlayerMovementComponent : public ActorMovementComponent {
	
	private:
		double _momentum(double * timer);
		
	public:
		PlayerMovementComponent() = delete;
		explicit PlayerMovementComponent(Entity *p);
		void update(double dt) override;
	
};