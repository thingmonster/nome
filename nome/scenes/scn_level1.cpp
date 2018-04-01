
#include "scn_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../components/cmp_actor_movement.h"
#include "../components/cmp_player_movement.h"
#include "../game.h"
#include "levelsystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void Level1Scene::update(const double& dt) {
	_ents.update(dt);
	
}

void Level1Scene::render() {
	ls::render(Renderer::getWindow());
	_ents.render();
}

void Level1Scene::load() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
	
	auto pl = Level1Scene::makeEntity();
	pl->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(20.f);
	s->getShape().setFillColor({208 , 62, 25});
	s->getShape().setOrigin(Vector2f(20.f, 20.f));
	auto m = pl->addComponent<PlayerMovementComponent>();
	m->setSpeed(200.f);
	
	
}






