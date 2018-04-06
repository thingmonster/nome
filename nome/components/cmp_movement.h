#pragma once
#include "ecm.h"
#include "levelsystem.h"
#include "engine.h"
#include "../classes/steering.h"

class MovementComponent : public Component {
	
	protected:
		bool validMove(const sf::Vector2f&);
		float _speed;
		
	public:
		explicit MovementComponent(Entity* p);
		MovementComponent() = delete;
		
		float getSpeed() const;
		void setSpeed(float _speed);
		
		bool move(const sf::Vector2f&);
		bool move(float x, float y);
		
		void render() override {}
		void update(double dt) override;
		
};