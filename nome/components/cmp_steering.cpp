
#include "cmp_steering.h"

using namespace sf;
using namespace std;

/*

used to be functional but might not be any more! 
not used in current implementation because steering 
is handled from state machine component


*/

SteeringComponent::SteeringComponent(Entity* p, Entity *player) : 
	_player(player), 
	_seek(SeekSteering(p, player, 100.0f)),
	_flee(FleeSteering(p, player, 100.0f)), 
	_wander(WanderSteering(p, player, 100.0f)), 
	MovementComponent(p) {
		
}

	
void SteeringComponent::update(double dt) {
	
/* 
	if (length(_parent->getPosition() - _player->getPosition()) > 500.0f) {
		auto output = _seek.getSteering();
		move(output.direction * (float)dt);
		_direction = output.direction;
	} else if (length(_parent->getPosition() - _player->getPosition()) < 50.0f) {
		auto output = _flee.getSteering();
		move(output.direction * (float)dt);
		_direction = output.direction;
	} else if (state == "stationary") {
		auto output = _flee.getSteering();
		move(output.direction * (float)dt);
		_direction = output.direction;
	} else {
		auto output = _wander.getSteering(_direction);
		if (_direction.x == 0 && _direction.y == 0) {
			output = _wander.getSteering();
			move(output.direction * (float)dt);
		} else {
			if (move(output.direction * (float)dt)) {
			} else {
				output = _wander.getSteering();
				move(output.direction * (float)dt);
			}
		}
		_direction = output.direction;
	}  */
}










