#include "ecm.h"

	
// ======================== ENTITY ======================== //
	
	
void Entity::setPosition(const Vector2f &pos) {
	_position = pos;
}

const Vector2f Entity::getPosition() {
	return _position;
}


void Entity::setVisible(bool v) {
	_visible = v;
}

bool Entity::getVisible() {
	return _visible;
}


std::string Entity::getTag() {
	return _tag;
}


void Entity::setForDelete() {
	_fordeletion = true;
}

bool Entity::is_fordeletion() {
	return _fordeletion;
}



void Entity::update(const double dt) {}

void Entity::render() {
	for (auto& c : _components) {
		c->render();
	}
}

Entity::Entity(Scene* s) : scene(s), _fordeletion(false) {}

Entity::Entity(Scene* s, std::string tag) : scene(s), _fordeletion(false), _tag(tag) {}

Entity::Entity(Scene* s, Vector2f pos) : scene(s), _position(pos), _fordeletion(false) {}

Entity::~Entity() {
	
	int deli = 0;
  while (deli != _components.size()) {
		deli = _components.size();
		_components.erase(
			remove_if(_components.begin(), _components.end(), [](auto& sp) { 
				return (sp.use_count() <= 1); 
			}), _components.end()
		);
  }

  if (_components.size() > 0) {
    cout << "Can't delete entity, someone is grabbing a component!" << endl;
  }

  _components.clear();
}



// ======================== ENTITY MANAGER ======================== //
	

void EntityManager::update(double dt) {
	
	for (int i = list.size() - 1; i >= 0; i--) {
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin() + i);
			cout << i << endl;
		}
	}
	
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



