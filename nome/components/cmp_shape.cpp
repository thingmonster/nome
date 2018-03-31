

#include "cmp_shape.h"



using namespace sf;
using namespace std;

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(make_shared<sf::CircleShape>()) {}







