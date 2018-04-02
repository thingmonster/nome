
#include "cmp_enemy_movement.h"

using namespace sf;
using namespace std;

void EnemyMovementComponent::update(double dt) {
	
	// 3% chance the beetle will change direction
	// otherwise it will continue on its current path
	
	int direction = rand() % 100;
	float moveX = 0.f;
	float moveY = 0.f;
	
	if ((direction == 0) || (direction > 3 && _direction == 0)) {
		moveY = _speed * -1;
		_direction = 0;
	} else if ((direction == 1) || (direction > 3 && _direction == 1)) {
		moveY = _speed;
		_direction = 1;
	} else if ((direction == 2) || (direction > 3 && _direction == 2)) {
		moveX = _speed * -1;
		_direction = 2;
	} else if ((direction == 3) || (direction > 3 && _direction == 3)) {
		moveX = _speed;
		_direction = 3;
	}
	
	moveX *= dt;
	moveY *= dt;
	
	float floatX = (float)moveX;
	float floatY = (float)moveY;
	
	move({floatX, floatY});
	
}



EnemyMovementComponent::EnemyMovementComponent(Entity *p) : ActorMovementComponent(p) {
}











