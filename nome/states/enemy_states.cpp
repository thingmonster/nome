#include "enemy_states.h"
#include "../components/cmp_shape.h"

using namespace sf;

void NormalState::execute(Entity *owner, double dt) noexcept {
	
	auto s = owner->getComponents<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Yellow);
	
	if (length(owner->getPosition() - _player->getPosition()) < 100.f) {
		auto sm = owner->getComponents<StateMachineComponent>();
		sm[0]->changeState("near");
	}
}

void NearState::execute(Entity *owner, double dt) noexcept {
	
	auto s = owner->getComponents<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Green);
	
	if (length(owner->getPosition() - _player->getPosition()) > 100.f) {
		auto sm = owner->getComponents<StateMachineComponent>();
		sm[0]->changeState("normal");
	}
}


