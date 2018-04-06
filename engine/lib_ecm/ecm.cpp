#include "ecm.h"

	
// ======================== ENTITY ======================== //
	
	
const Vector2f Entity::getPosition() {
	return _position;
}

void Entity::setPosition(const Vector2f &pos) {
	_position = pos;
}

void Entity::setVisible(bool v) {
	cout << "hi";
	_visible = v;
}

bool Entity::getVisible() {
	return _visible;
}

// void Entity::setForDelete() {
	// _fordeletion = true;
// }

// bool Entity::is_fordeletion() {
	// return _fordeletion;
// }

// float Entity::getRadius() {
	// return _radius;
// }

// void Entity::move(const Vector2f &pos) {
	// _position += pos;
// }

void Entity::update(const double dt) {}

void Entity::render() {
	for (auto& c : _components) {
		c->render();
	}
}

Entity::Entity(Scene* s) : scene(s), _fordeletion(false) {}




// ======================== ENTITY MANAGER ======================== //
	

void EntityManager::update(double dt) {
	
	for (auto &e : list) {
		for (auto &c : e->_components) {
			c->update(dt);
		}
	}
}
	
void EntityManager::render() {
	
	for (auto &e : list) {
		e->render();
	}
}
	
	
	
	
// ======================== COMPONENT ======================== //
	
	
Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}

Component::~Component() {}



