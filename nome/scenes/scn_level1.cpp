
#include "scn_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../components/cmp_actor_movement.h"
#include "../components/cmp_player_movement.h"
#include "../components/cmp_enemy_movement.h"
#include "../game.h"
#include "levelsystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> Level1Scene::playerSprites;
std::shared_ptr<sf::Texture> Level1Scene::enemySprites;

void Level1Scene::update(const double& dt) {
	
	_ents.update(dt);
	
	static double timer = 1.0f;
	timer -= dt;
	if (timer < 0.f)  {
		cout << maxEnemies << endl;
		if (maxEnemies > 0) {
			spawn();
			maxEnemies--;
		}
		timer = 4.f;
	}
	
}

void Level1Scene::render() {
	ls::render(Renderer::getWindow());
	_ents.render();
}

void Level1Scene::load() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
	
	playerSprites = Resources::get<sf::Texture>("player.png");
	enemySprites = Resources::get<sf::Texture>("beetles-black.png");
	
	
	
	player = Level1Scene::makeEntity();
	player->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(20.f);
	s->getShape().setFillColor({255 , 255, 255});
	s->getShape().setOrigin(Vector2f(20.f, 20.f));
	s->setTexture(playerSprites, sf::IntRect(0,0,50,50));
	auto m = player->addComponent<PlayerMovementComponent>();
	m->setSpeed(200.f);
	
	auto ball = Level1Scene::makeEntity();
	ball->setPosition(ls::getTileCentre(ls::findTiles(ls::BALL)[0]));
	auto b = ball->addComponent<ShapeComponent>();
	b->setShape<sf::CircleShape>(20.f);
	b->getShape().setFillColor({255 , 255, 255});
	b->getShape().setOrigin(Vector2f(20.f, 20.f));
	b->setTexture(playerSprites, sf::IntRect(50,0,50,50));
	// add ball movement component here?
	
}

void Level1Scene::spawn() {
	
	auto beetle = Level1Scene::makeEntity();
	beetle->setPosition(ls::getTileCentre(ls::findTiles(ls::HOLE)[0]));
	auto shape = beetle->addComponent<ShapeComponent>();
	shape->setShape<sf::CircleShape>(20.f);
	shape->getShape().setFillColor({255 , 255, 255});
	shape->getShape().setOrigin(Vector2f(20.f, 20.f));
	shape->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	auto move = beetle->addComponent<EnemyMovementComponent>(player.get());
	
}






