
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void LoadScene::update(const double& dt) {
	
	
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		loadGame();
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
	}
	
}

void LoadScene::load() {
	
	levels.push_back(&level1);
	
	Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

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
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
	// ============================== CONTENT ============================== // 
	
	// "Load Game"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Load Game", "WorstveldSling.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(100);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 170});
	
	
		
	// ============================== FOOT ============================== // 
	
	// "press enter to resume"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press ENTER to resume", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	//  C to cancel
	auto cr = makeEntity();
	auto c = cr->addComponent<TextComponent>("or TAB to cancel and go back", "WorstveldSling.ttf");
	c->setColor(sf::Color(200 , 190, 183));
	c->setCharacterSize(40);
	c->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 4, windowSize.y - 70});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void LoadScene::unload() {
	
  _ents.list.clear();
	
}

void LoadScene::reload() {
	
}

void LoadScene::loadGame() {
	
		bool topLineBeenRead = false;
	
		ifstream savedGame ("test.txt");
		
		string str;
		if (savedGame.is_open()) {
			while (getline(savedGame, str)) {
				if (!topLineBeenRead) {
					int level = std::stoi(str) - 1;
					Engine::changeLevel(levels[level]);
					// get level, 
					// load level, 
					// destroy current level?
					topLineBeenRead = true;
				} else {
					// loadEntity(str);
				}
			}
			savedGame.close();
		} else {
			cout << "Unable to open file" << endl; 
		}

		Engine::goToGame();
}

// void LoadScene::loadEntity(std::string s) {
	
	
	
// }
