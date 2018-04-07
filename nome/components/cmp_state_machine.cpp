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
	s[0]->getShape().setFillColor(Color::Red);
}

void SeekState::execute(Entity *owner, double dt) noexcept {
	// cout << "seek" << endl;
	auto s = owner->getComponents<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Green);
	auto output = _steering.getSteering();
	float speed = 1;
	owner->setPosition(owner->getPosition() + (output.direction * _speed * (float)dt));
}

void FleeState::execute(Entity *owner, double dt) noexcept {
	// cout << "flee" << endl;
	auto s = owner->getComponents<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Yellow);
	auto output = _steering.getSteering();
	float speed = 1;
	owner->setPosition(owner->getPosition() + (output.direction * _speed * (float)dt));
}




