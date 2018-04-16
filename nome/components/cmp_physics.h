#pragma once

#include "engine.h"
#include "../game.h"
#include <Box2D/Dynamics/b2Body.h>

/* 

this file contains definitions for physics component and 
also player physics component and enemy physics component

*/

class PhysicsComponent : public Component {
	protected:
		b2Body* _body;
		const bool _dynamic;
		b2Fixture* _fixture;

	public:
		PhysicsComponent(Entity* p, bool dyn, const sf::Vector2f& size);

		void PhysicsComponent::setRestitution(float r);
		bool isTouching(const PhysicsComponent& pc) const;
		bool isTouching(const PhysicsComponent& pc, b2Contact const* bc) const;
		std::vector<const b2Contact*> getTouching() const;
		const sf::Vector2f getVelocity() const;
		void update(double dt) override;
		void render() override;
		void impulse(const sf::Vector2f& i);
		void dampen(const sf::Vector2f& s);
		void setVelocity(const sf::Vector2f& v);
		~PhysicsComponent() override;
};
		

class PlayerPhysicsComponent : public PhysicsComponent {
	
	protected:
		b2Vec2 _size;
		sf::Vector2f _maxVelocity;
		float _speed;
		bool checkContacts() const;

	public:
		void update(double dt) override;
		explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size, float speed);
		PlayerPhysicsComponent() = delete;
		
};

class EnemyPhysicsComponent : public PhysicsComponent {
		
	protected:
		b2Vec2 _size;
		sf::Vector2f _maxVelocity;
		float _speed;
		Vector2f _direction;
		bool checkContacts() const;

	public:
		void update(double dt) override;
		explicit EnemyPhysicsComponent(Entity* p, const sf::Vector2f& size, float speed);
		EnemyPhysicsComponent() = delete;
		void setDirection(Vector2f direction);
		Vector2f getDirection();
		
};

class BallPhysicsComponent : public PhysicsComponent {
		
	protected:
		b2Vec2 _size;
		sf::Vector2f _maxVelocity;
		float _speed;
		bool checkContacts() const;

	public:
		void update(double dt) override;
		explicit BallPhysicsComponent(Entity* p, const sf::Vector2f& size, float speed);
		BallPhysicsComponent() = delete;
		
};









