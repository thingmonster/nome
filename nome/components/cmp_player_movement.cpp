
#include "cmp_player_movement.h"

using namespace sf;
using namespace std;

const Keyboard::Key controls[] = {
    Keyboard::Left,
    Keyboard::Right,
    Keyboard::Up,
    Keyboard::Down
};

double PlayerMovementComponent::_momentum(double * timer) {
	
	double move = 0;

	move = _speed - pow( 210 - *timer * 20, 2);
	if (move < 0) {
		move = 0;
		*timer = 0;
	}

	return move;
	
}

void PlayerMovementComponent::update(double dt) {
	
	
	
	// player movement with momentum
	
	double moveLeft = 0;
	double moveRight = 0;
	double moveUp = 0;
	double moveDown = 0;
	
	static double lastMoveLeft = 0.0f;
	static double lastMoveRight = 0.0f;
	static double lastMoveUp = 0.0f;
	static double lastMoveDown = 0.0f;
	
	lastMoveLeft -= dt;
	lastMoveRight -= dt;
	lastMoveUp -= dt;
	lastMoveDown -= dt;
	
	// get current direction and apply momentum from recent moves
	
	if (Keyboard::isKeyPressed(controls[0])) {
		lastMoveLeft = 10.f;
		moveLeft = _speed * -1;
	} else {
		if (lastMoveLeft > 0) {
			moveLeft = _momentum(&lastMoveLeft) * -1;
		}
	}
	
	if (Keyboard::isKeyPressed(controls[1])) {
		lastMoveRight = 10.f;
		moveRight = _speed;
	} else {
		if (lastMoveRight > 0) {
			moveRight = _momentum(&lastMoveRight);
		}
	}
	
	if (Keyboard::isKeyPressed(controls[2])) {
		lastMoveUp = 10.f;
		moveUp = _speed * -1;
	} else {
		if (lastMoveUp > 0) {
			moveUp = _momentum(&lastMoveUp) * -1;
		}
	}
	
	if (Keyboard::isKeyPressed(controls[3])) {
		lastMoveDown = 10.f;
		moveDown = _speed;
	} else {
		if (lastMoveDown > 0) {
			moveDown = _momentum(&lastMoveDown);
		}
	}

	// update player's position
	
	float x = _parent->getPosition().x;
	float y = _parent->getPosition().y;
	
	x += (moveLeft * dt) + (moveRight * dt);
	y += (moveUp * dt) + (moveDown * dt);
	
	float moveX = (moveLeft * dt) + (moveRight * dt);
	float moveY = (moveUp * dt) + (moveDown * dt);
	
	float floatX = (float)moveX;
	float floatY = (float)moveY;
	
	move({floatX, floatY});
	ActorMovementComponent::update(dt);
}

PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p) {}
