#pragma once
#include "ecm.h"
#include "levelsystem.h"
#include "../classes/steering.h"

class ActorMovementComponent : public Component {
	
	protected:
		bool validMove(const sf::Vector2f&);
		float _speed;
		
	public:
		explicit ActorMovementComponent(Entity* p);
		ActorMovementComponent() = delete;
		
		float getSpeed() const;
		void setSpeed(float _speed);
		
		bool move(const sf::Vector2f&);
		bool move(float x, float y);
		
		void render() override {}
		void update(double dt) override;
		
};