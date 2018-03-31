
#include "scn_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void MenuScene::update(const double& dt) {}

void MenuScene::load() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// "game engine skeleton"
	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("Game Engine Skeleton", "Rubik-Medium.ttf");
	t->setColor(sf::Color(200 , 190, 183));
	t->setCharacterSize(50);
	t->SetPosition({windowSize.x / 2 - t->getText().getLocalBounds().width / 2, 220});
	
	
}






