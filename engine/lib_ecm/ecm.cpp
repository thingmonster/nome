#include "ecm.h"

	
// ======================== ENTITY ======================== //
	
	
void Entity::update(const double dt) {}

void Entity::render() {
	for (auto& c : _components) {
		c->render();
	}
}

Entity::Entity(Scene* s) : scene(s), _fordeletion(false) {}




// ======================== ENTITY MANAGER ======================== //
	

void EntityManager::update(double dt) {
	
	cout << "EM-update ";
	
}
	
void EntityManager::render() {
	
	cout << "EM-render ";
	
}
	
	
	

