
#include "scn_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void MenuScene::update(const double& dt) {
	
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		cout << "enter" << endl;
		Engine::changeScene(&level1);
		
	}
	
}

void MenuScene::load() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// background	
	auto background = makeEntity();
	auto b = background->addComponent<ShapeComponent>();
	b->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x, windowSize.y));
	b->getShape().setPosition(sf::Vector2f(0,0));
	b->getShape().setFillColor(sf::Color(72,62,55));
	
	// "story of nome"
	auto son = makeEntity();
	auto sn = son->addComponent<TextComponent>("The Story of Nome", "WorstveldSling.ttf");
	sn->setColor(sf::Color(200 , 190, 183));
	sn->setCharacterSize(75);
	sn->SetPosition({windowSize.x / 2 - sn->getText().getLocalBounds().width / 2, 10});
	
	// "use the ball to kill the beetles"
	auto ubkb = makeEntity();
	auto ub = ubkb->addComponent<TextComponent>("Use the ball to kill the beetles", "WorstveldSling.ttf");
	ub->setColor(sf::Color(200 , 190, 183));
	ub->setCharacterSize(35);
	ub->SetPosition({windowSize.x / 2 - ub->getText().getLocalBounds().width / 2, 420});
	
	// "rest is up to you"
	auto riuty = makeEntity();
	auto ri = riuty->addComponent<TextComponent>("The rest is up to you...", "WorstveldSling.ttf");
	ri->setColor(sf::Color(200 , 190, 183));
	ri->setCharacterSize(25);
	ri->SetPosition({windowSize.x / 2 - ri->getText().getLocalBounds().width / 2, 460});
	
	// "press enter to begin"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press enter to begin", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, 490});
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	// line
	auto line2 = makeEntity();
	auto s2 = line->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, 410));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	// "game engine skeleton"
	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("Game Engine Skeleton", "Rubik-Medium.ttf");
	t->setColor(sf::Color(200 , 190, 183));
	t->setCharacterSize(50);
	t->SetPosition({windowSize.x / 2 - t->getText().getLocalBounds().width / 2, 220});
	
	
}






