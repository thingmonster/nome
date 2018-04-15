#include "cmp_physics.h"
#include "physics.h"

using namespace std;
using namespace sf;

using namespace Physics;



PhysicsComponent::PhysicsComponent(Entity* p, bool dyn, const Vector2f& size) : Component(p), _dynamic(dyn) {
	
	/*
	
	this method does not differ much from the platformer
	component in the module repo, just a couple of settings
	tweaked

	*/
	
  b2BodyDef BodyDef;
  BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
  BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

  // Create the body
  _body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetUserData(p);
  _body->SetActive(true);

	// Create the fixture shape
	b2PolygonShape Shape;

	// SetAsBox box takes HALF-Widths!
	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	b2FixtureDef FixtureDef;
	FixtureDef.friction = _dynamic ? 1.f : 0.8f;
	FixtureDef.restitution = .1;
	FixtureDef.shape = &Shape;

	// Add to body
	_fixture = _body->CreateFixture(&FixtureDef);


}

PhysicsComponent::~PhysicsComponent() {
	// slight changes because we were getting runtime exceptions
	if (Physics::GetWorld() != nullptr) {
		_body->SetActive(false);
		Physics::GetWorld()->DestroyBody(_body);
		_body = nullptr;
	}
}

void PhysicsComponent::update(double dt) {
  _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
	// very slight dampening applied to all bodies
	dampen({0.995f, 0.995f});	
}

void PhysicsComponent::render() {}


void PhysicsComponent::impulse(const sf::Vector2f& i) {
	// identical to platformer
  auto a = b2Vec2(i.x, i.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& s) {
	// identical to platformer
  auto vel = _body->GetLinearVelocity();
  vel.x *= s.x;
  vel.y *= s.y;
	_body->SetLinearVelocity(vel);
}


std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  
	// identical to platformer
	
	std::vector<const b2Contact const*> ret;
  b2ContactEdge* edge = _body->GetContactList();

  while (edge != NULL) {
		const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
	// not yet implemented :(
	return true;
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc, b2Contact const* bc) const {
	// not yet implemented :(
	return true;
}

void PhysicsComponent::setRestitution(float r) {
	// identical to platformer
	_fixture->SetRestitution(r);
}

void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
	// identical to platformer
	_body->SetLinearVelocity(sv2_to_bv2(v, true));
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
	// identical to platformer
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}








PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) 
: PhysicsComponent(p, true, size) {
	// based mostly on platformer player physics component constructor
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(400.f, 400.f);
  _speed = 50.f;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(false);
	_fixture->SetRestitution(.1);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}

void PlayerPhysicsComponent::update(double dt) {
	
  const auto pos = _parent->getPosition();
	
	// ============ go up ============
	if (
		(Keyboard::isKeyPressed(Keyboard::Up)) || 
		(Joystick::getAxisPosition(0, Joystick::Axis::Y) < -60.00f)//up 
	)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({0, -(float)(dt * _speed)});
		}
	} 
	else if (Joystick::getAxisPosition(0, Joystick::Axis::Y) < -20.00f)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({ 0, -(float)(dt * (_speed / 3)) });
		}
	}
	
	
	// ============ go down ============
	if (
		(Keyboard::isKeyPressed(Keyboard::Down)) || 
		(Joystick::getAxisPosition(0, Joystick::Axis::Y) > 60.00f)//down
	)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({0, (float)(dt * _speed)});
		}
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::Y) > 20.00f)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({ 0, (float)(dt * (_speed / 3)) });
		}
	}
	
	
	// ============ go right ============
	if (
		(Keyboard::isKeyPressed(Keyboard::Right)) || 
		(Joystick::getAxisPosition(0, Joystick::Axis::X) > 60.00f)//right
	)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({(float)(dt * _speed), 0});
		}
	} 
	else if (Joystick::getAxisPosition(0, Joystick::Axis::X) > 20.00f)
	{
		if (getVelocity().x < _maxVelocity.x) {
			impulse({ (float)(dt * (_speed / 3)), 0 });
		}
	}
	
	
	// ============ go left ============
	if (
		(Keyboard::isKeyPressed(Keyboard::Left)) || 
		(Joystick::getAxisPosition(0, Joystick::Axis::X) < -60.00f)//left
	)
	{
		if (getVelocity().x > -_maxVelocity.x) {
			impulse({-(float)(dt * _speed), 0});
		}
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::X) < -20.00f)
	{
		if (getVelocity().x > -_maxVelocity.x) {
			impulse({ -(float)(dt * (_speed / 3) ), 0 });
		}
	}
	
	// apply extra dampening to player body
	dampen({0.92f, 0.92f});
	
	// check for contact with other bodies
	checkContacts();

	// clamp velocity?
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

	// set parent entity's rotation
	auto shape = _parent->getComponents<ShapeComponent>();
	shape[0]->setRotation(inverseVector2degrees(v));
	
	// update parent entity's position
  PhysicsComponent::update(dt);
}

bool PlayerPhysicsComponent::checkContacts() const {
	
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	
	// for each body touched
	for (const auto& contact : touch) {
		
		// get entity tags from user data
		
		std::string tagA;
		std::string tagB;
		
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		if ( bodyUserDataA ) {
			Entity* entityA = static_cast<Entity*>( contact->GetFixtureA()->GetBody()->GetUserData() );
			if (entityA != NULL) {
				tagA = entityA->getTag();
			}
		}
		
		void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
		if ( bodyUserDataB ) {
			Entity* entityB = static_cast<Entity*>( contact->GetFixtureB()->GetBody()->GetUserData() );
			if (entityB != NULL) {
				tagB = entityB->getTag();
			}
		}
		
		// this is the player so we know that if he touches a beetle he's dead
		if ((tagA == "beetle") || (tagB == "beetle")) {
			_parent->setVisible(false);
			Engine::changeScene(&death);
		}
		
		
	}
	
  return false;
}









EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p, const Vector2f& size) 
: PhysicsComponent(p, true, size) {
  // based mostly on platformer player physics component constructor
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(400.f, 400.f);
  _speed = 30.f;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  // Bullet items have higher-res collision detection
  _body->SetBullet(true);
}

void EnemyPhysicsComponent::update(double dt) {
	//check collistions
	checkContacts();
	// move to position determined by state machine and steering behaviour
	// this could be updated to calculate the direction by comparing body and entity positions,
	// applying an impulse in that direction, and then updating entity position
	_body->SetTransform(sv2_to_bv2(invert_height(_parent->getPosition())), 1 );
}

bool EnemyPhysicsComponent::checkContacts() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	
	// for each body that's been touched
	for (const auto& contact : touch) {
		
		// get the entity's tag from user data
		std::string tagA;
		std::string tagB;
		
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		if ( bodyUserDataA ) {
			Entity* entityA = static_cast<Entity*>( contact->GetFixtureA()->GetBody()->GetUserData() );
			if (entityA != NULL) {
				tagA = entityA->getTag();
			}
		}
		
		void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
		if ( bodyUserDataB ) {
			Entity* entityB = static_cast<Entity*>( contact->GetFixtureB()->GetBody()->GetUserData() );
			if (entityB != NULL) {
				tagB = entityB->getTag();
			}
		}
		
		// this is a beetle so we know that if it's touched the ball it's dead
		if ((tagA == "ball") || (tagB == "ball")) {
			
			// should be updated so that the beetle died but is not deleted immediately
			Engine::getLevel()->setDeathCount();
			_parent->setVisible(false);
			_parent->setForDelete();
		}
		
		
		return true;
	}
	
  return false;
}
















