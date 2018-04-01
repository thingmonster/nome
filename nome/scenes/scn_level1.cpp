
#include "scn_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include "levelsystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void Level1Scene::update(const double& dt) {
	// cout << "Level1Scene update" << endl;
}

void Level1Scene::render() {
	ls::render(Renderer::getWindow());
}

void Level1Scene::load() {
	
	ls::loadLevel("res/levels/level1.txt", 30.f);
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// "Level 1 goes here"
	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("Level 1 goes here", "Rubik-Medium.ttf");
	t->setColor(sf::Color(200 , 190, 183));
	t->setCharacterSize(50);
	t->SetPosition({windowSize.x / 2 - t->getText().getLocalBounds().width / 2, 220});
	
	
}






