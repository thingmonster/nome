
#include "cmp_player_movement.h"
#include <iostream>	
using namespace sf;
using namespace std;


/*

this was the original player movement component before we added
box2d... it had quite nice momentum and I would have used 
my diagonal circle vs square collision detector if box2d hadn't 
been part of the module. instead you can only find it in
lab 3 in my other repo https://github.com/thingmonster/set09121


*/

double PlayerMovementComponent::_momentum(double * timer) {
	
	double move = 0;

	move = _speed - pow( 210 - *timer * 20, 2);
	if (move < 0) {
		move = 0;
		*timer = 0;
	}

	return move;
	
}

void PlayerMovementComponent::update(double dt) 
{
	//testing axes
	/*
	std::cout << "Current X Axis: " << Joystick::getAxisPosition(0, Joystick::X) << std::endl;
	std::cout << "Current Y Axis: " << Joystick::getAxisPosition(0, Joystick::Y) << std::endl;
	*/

	//testing buttons
	/*
	if (Joystick::isButtonPressed(0, 0))
	{
	std::cout << "cross" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 1))
	{
	std::cout << "circle" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 2))
	{
	std::cout << "square" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 3))
	{
	std::cout << "triangle" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 4))
	{
	std::cout << "L1" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 5))
	{
	std::cout << "R1" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 6))
	{
	std::cout << "Select" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 7))
	{
	std::cout << "Start" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 8))
	{
	std::cout << "L3" << std::endl;
	}
	if (Joystick::isButtonPressed(0, 9))
	{
	std::cout << "R3" << std::endl;
	}
	*/
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
	
	if ((Keyboard::isKeyPressed(Engine::controls[0])) || (Joystick::getAxisPosition(0, Joystick::Axis::X) < -60.00f))//left
	{
		lastMoveLeft = 10.f;
		moveLeft = _speed * -1;
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::X) < -20.00f)
	{
		moveLeft = (_speed / 3) * -1;
	}
	else 
	{
		if (lastMoveLeft > 0) {
			moveLeft = _momentum(&lastMoveLeft) * -1;
		}
	}//end left

	if ((Keyboard::isKeyPressed(Engine::controls[1])) || (Joystick::getAxisPosition(0, Joystick::Axis::X) > 60.00f))//right
	{
		lastMoveRight = 10.f;
		moveRight = _speed;
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::X) > 20.00f)
	{
		moveRight = (_speed / 3);
	}
	else 
	{
		if (lastMoveRight > 0) {
			moveRight = _momentum(&lastMoveRight);
		}
	}//end right

	if ((Keyboard::isKeyPressed(Engine::controls[2])) || (Joystick::getAxisPosition(0, Joystick::Axis::Y) < -60.00f))//up
	{
		lastMoveUp = 10.f;
		moveUp = _speed * -1;
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::Y) < -20.00f)
	{
		moveUp = (_speed / 3) * -1;
	}
	else 
	{
		if (lastMoveUp > 0) {
			moveUp = _momentum(&lastMoveUp) * -1;
		}
	}//end up

	if ((Keyboard::isKeyPressed(Engine::controls[3])) || (Joystick::getAxisPosition(0, Joystick::Axis::Y) > 60.00f))//down
	{
		lastMoveDown = 10.f;
		moveDown = _speed;
	}
	else if (Joystick::getAxisPosition(0, Joystick::Axis::Y) > 20.00f)
	{
		moveDown = (_speed / 3);
	}
	else 
	{
		if (lastMoveDown > 0) {
			moveDown = _momentum(&lastMoveDown);
		}
	}//end down
	
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
	MovementComponent::update(dt);
}

PlayerMovementComponent::PlayerMovementComponent(Entity *p) : MovementComponent(p) {}
