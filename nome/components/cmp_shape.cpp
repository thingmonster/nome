

#include "cmp_shape.h"

/* 

just getters and setters, render, update and 
constructor in this class

*/

using namespace sf;
using namespace std;

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() {
	if (_parent->getVisible()) {
		Renderer::queue(_shape.get());
	}
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

void ShapeComponent::setRotation(float r) {
	_shape->setRotation(r);
}

void ShapeComponent::setTexture(std::shared_ptr<sf::Texture> t, sf::IntRect r) {
  _texture = t;
	getShape().setTexture(_texture.get());
	getShape().setTextureRect(r);
}

ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(make_shared<sf::CircleShape>()) {}







