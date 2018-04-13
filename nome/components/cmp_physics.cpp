#include "cmp_physics.h"
#include "physics.h"

using namespace std;
using namespace sf;

using namespace Physics;



PhysicsComponent::PhysicsComponent(Entity* p, bool dyn, const Vector2f& size) : Component(p), _dynamic(dyn) {

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
	FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
	FixtureDef.restitution = .2;
	FixtureDef.shape = &Shape;

	// Add to body
	_fixture = _body->CreateFixture(&FixtureDef);
	//_fixture->SetRestitution(.9)
	FixtureDef.restitution = .2;


}

PhysicsComponent::~PhysicsComponent() {
	if (Physics::GetWorld() != nullptr) {
		_body->SetActive(false);
		Physics::GetWorld()->DestroyBody(_body);
		_body = nullptr;
	}
}

void PhysicsComponent::update(double dt) {
  _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
	// _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

void PhysicsComponent::render() {
  // cout << "physics render" << endl;
}


const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
  auto a = b2Vec2(i.x, i.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& s) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= s.x;
  vel.y *= s.y;
	_body->SetLinearVelocity(vel);
}


std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  
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
	return true;
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc, b2Contact const* bc) const {
	return true;
}

void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
	_body->SetLinearVelocity(sv2_to_bv2(v, true));
}








PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(400.f, 400.f);
  _speed = 50.f;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(false);
  //Bullet items have higher-res collision detection
  // _body->SetBullet(true);
}

void PlayerPhysicsComponent::update(double dt) {
	
  const auto pos = _parent->getPosition();
	
	if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Joystick::getAxisPosition(0, Joystick::Axis::Y) < -60.00f))//up 
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
	if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Joystick::getAxisPosition(0, Joystick::Axis::Y) > 60.00f))//down
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
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Joystick::getAxisPosition(0, Joystick::Axis::X) > 60.00f))//right
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
	if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Joystick::getAxisPosition(0, Joystick::Axis::X) < -60.00f))//left
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
	
	dampen({0.9f, 1.0f});
	dampen({1.0f, .9f});
	
	checkContacts();

  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

	auto shape = _parent->getComponents<ShapeComponent>();
	shape[0]->setRotation(vector2degrees(v));
	
  PhysicsComponent::update(dt);
}

bool PlayerPhysicsComponent::checkContacts() const {
	
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	for (const auto& contact : touch) {
		
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
		
		if ((tagA == "beetle") || (tagB == "beetle")) {
			_parent->setVisible(false);
			cout << "beetle / player" << endl;
			Engine::changeScene(&death);
		}
		
		
	}
	
  return false;
}









EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(400.f, 400.f);
  _speed = 30.f;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  // Bullet items have higher-res collision detection
  _body->SetBullet(true);
}

void EnemyPhysicsComponent::update(double dt) {
	
	checkContacts();
	_body->SetTransform(sv2_to_bv2(invert_height(_parent->getPosition())), 1 );
	
}

bool EnemyPhysicsComponent::checkContacts() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	for (const auto& contact : touch) {
		
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
		
		if ((tagA == "ball") || (tagB == "ball")) {
			Engine::getLevel()->setDeathCount();
			_parent->setVisible(false);
			_parent->setForDelete();
			cout << "beetle / ball" << endl;
		}
		
		
		return true;
	}
	
  return false;
}
















