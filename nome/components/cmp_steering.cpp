
#include "cmp_steering.h"

using namespace sf;
using namespace std;



SteeringComponent::SteeringComponent(Entity* p, Entity *player) : 
	_player(player), 
	_seek(Seek(p, player, 100.0f)),
	_flee(Flee(p, player, 100.0f)), 
	_wander(Wander(p, player, 100.0f)), 
	MovementComponent(p) {
		
	}

	
void SteeringComponent::update(double dt) {
	if (length(_parent->getPosition() - _player->getPosition()) > 500.0f) {
		auto output = _seek.getSteering();
		move(output.direction * (float)dt);
		_direction = output.direction;
	} else if (length(_parent->getPosition() - _player->getPosition()) < 50.0f) {
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
	}
}










