#include "cmp_state_machine.h"

using namespace std;

StateMachineComponent::StateMachineComponent(Entity *p)
 : _current_state(nullptr), Component(p) {}

void StateMachineComponent::update(double dt) {
	if (_current_state != nullptr) {
		_current_state->execute(_parent, dt);
	}
}

void StateMachineComponent::addState(const string &name, shared_ptr<State> state) noexcept {
	_states[name] = state;
}

shared_ptr<State> StateMachineComponent::getState(const string &name) const noexcept {
	auto found = _states.find(name);
	if (found != _states.end()) {
		return found->second;
	} else {
		return nullptr;
	}
}

void StateMachineComponent::removeState(const string &name) noexcept {
	_states.erase(name);
}

void StateMachineComponent::changeState(const string &name) noexcept {
	auto found = _states.find(name);
	if (found != _states.end()) {
		_current_state = found->second;
		_current_state_name = name;
	}
}



 



void StationaryState::execute(Entity *owner, double dt) noexcept {
	// cout << "stationary" << endl;
	auto s = owner->getComponents<ShapeComponent>();
	// s[0]->getShape().setFillColor(Color::Red);
}

void SeekState::execute(Entity *owner, double dt) noexcept {
	// cout << "seek" << endl;
	
	auto output = _steering.getSteering();
	auto movement = owner->getComponents<MovementComponent>();
	movement[0]->move((output.direction * _speed * (float)dt));
	movement[0]->setDirection( output.direction);
		
	auto shape = owner->getComponents<ShapeComponent>();
	shape[0]->getShape().setRotation(output.rotation);
}

void FleeState::execute(Entity *owner, double dt) noexcept {
	// cout << "flee" << endl;
	
	auto output = _steering.getSteering();
	auto movement = owner->getComponents<MovementComponent>();
	movement[0]->move((output.direction * _speed * (float)dt));
	movement[0]->setDirection( output.direction);
	
	auto shape = owner->getComponents<ShapeComponent>();
	shape[0]->getShape().setRotation(output.rotation);
}

void WanderState::execute(Entity *owner, double dt) noexcept {
	// cout << "wander" << endl;
	
	auto movement = owner->getComponents<MovementComponent>();
	sf::Vector2f direction = movement[0]->getDirection();
	
	auto output = _steering.getSteering(direction);
	movement[0]->setDirection( output.direction);
	
	if (!movement[0]->move((output.direction * _speed * (float)dt)))  {
		output = _steering.getSteering();
		movement[0]->move(output.direction * _speed * (float)dt);
	}
	
	movement[0]->setDirection( output.direction);
	
	auto shape = owner->getComponents<ShapeComponent>();
	shape[0]->getShape().setRotation(output.rotation);
	
}




