
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
	
	int line = 1;
	int level = -1;
	std::string entity;
	std::vector<std::shared_ptr<Entity>> entities;
	
	ifstream savedGame ("test.txt");
	
	string str;
	if (savedGame.is_open()) {
		while (getline(savedGame, str)) {
			if (line == 1) {
				level = std::stoi(str) - 1;
				line = 2;
			} else {
				// cout << str << endl;
				// loadEntity(str);
				// entity = loadEntity(str);
				// auto ptr = make_shared<Entity>();
				entities.push_back(loadEntity(str));
			}
		}
		savedGame.close();
	} else {
		cout << "Unable to open file" << endl; 
	}
	
	if (level >= 0) {
		Engine::changeLevel(levels[level]);
		Engine::restoreGame(entities);
	} else {
		cout << "no content in file" << endl;
	}
}

std::shared_ptr<Entity> LoadScene::loadEntity(std::string s) {
// void LoadScene::loadEntity(std::string s) {
	
	std::string delimiter = ",";

	size_t pos = 0;
	vector<std::string> tokens;
	std::string token;
	
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);
	
	sf::Vector2f p(stof(tokens[0]),stof(tokens[1]));
	
	auto e = make_shared<Entity>(this, p);
	return e;
}
