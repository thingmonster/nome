#pragma once
#include "cmp_movement.h"

class PlayerMovementComponent : public MovementComponent {
	
	private:
		double _momentum(double * timer);
		
	public:
		PlayerMovementComponent() = delete;
		explicit PlayerMovementComponent(Entity *p);
		void update(double dt) override;
	
};