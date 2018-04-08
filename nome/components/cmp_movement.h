#pragma once
// #include "ecm.h"
// #include "levelsystem.h"
#include "engine.h"
// #include "../classes/steering.h"

class MovementComponent : public Component {
	
	protected:
		bool validMove(const sf::Vector2f&);
		float _speed;
		sf::Vector2f _direction;
		
	public:
		explicit MovementComponent(Entity* p);
		MovementComponent() = delete;
		
		float getSpeed() const;
		void setSpeed(float speed);
		
		sf::Vector2f getDirection() const;
		void setDirection(sf::Vector2f direction);
		
		bool move(const sf::Vector2f&);
		bool move(float x, float y);
		
		void render() override {}
		void update(double dt) override;
		
};