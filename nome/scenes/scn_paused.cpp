
#include "scn_options.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;



void PausedScene::update(const double& dt) {
	
		
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		Engine::changeScene(&level1);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		Engine::changeScene(&menu);
	}
	
}

void PausedScene::makeDescription(std::string t, sf::Vector2f p) {
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "Rubik-Medium.ttf");
	text->setColor(sf::Color(200 , 190, 183));
	text->setCharacterSize(25);
	
	text->SetPosition(p);
	
}

void PausedScene::makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p) {
		
	auto entity = makeEntity();
	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	shape->getShape().setOrigin(20,20);
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, sf::IntRect(0,0,40,40));
	shape->getShape().setPosition(p);	
	
}

void PausedScene::makeKeyText(std::string t, sf::Vector2f p) {
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "DroidSansMono.ttf");
	text->setOrigin(text->getText().getLocalBounds().width / 2, text->getText().getLocalBounds().height / 2);
	text->setColor(sf::Color(72,62,55));
	text->setCharacterSize(25);
	text->SetPosition(p);
}

void PausedScene::resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p) {
	
	auto entity = makeEntity();
	entity->setVisible(v);

	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(s);
	shape->getShape().setOrigin(Vector2f(20,20));
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, r);
	shape->getShape().setPosition(p);
	
	
	
}

void PausedScene::load() {
	
  _ents.list.clear();
	
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
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
	// ============================== CONTENT ============================== // 
	
	// "Game Paused"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Game Paused", "WorstveldSling.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(100);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 170});
	
	// ============================== DESCRIPTIONS & KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	makeDescription("Options", sf::Vector2f(windowSize.x / 8 * 0 + 100, windowSize.y / 2 + 80));	
	makeDescription("Save Game",sf::Vector2f(windowSize.x / 8 * 2 + 80, windowSize.y / 2 + 80));	
	makeDescription("Load Game", sf::Vector2f(windowSize.x / 8 * 4 + 95, windowSize.y / 2 + 80));
	makeDescription("Quit", sf::Vector2f(windowSize.x / 8 * 6 + 110, windowSize.y / 2 + 80));
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 8 * 0 + 70, windowSize.y / 2 + 95));	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 8 * 2 + 50, windowSize.y / 2 + 95));	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 8 * 4 + 65, windowSize.y / 2 + 95));	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 8 * 6 + 80, windowSize.y / 2 + 95));	
	
	makeKeyText("O", sf::Vector2f(windowSize.x / 8 * 0 + 70, windowSize.y / 2 + 90));	
	makeKeyText("S", sf::Vector2f(windowSize.x / 8 * 2 + 50, windowSize.y / 2 + 90));	
	makeKeyText("L", sf::Vector2f(windowSize.x / 8 * 4 + 65, windowSize.y / 2 + 90));	
	makeKeyText("Q", sf::Vector2f(windowSize.x / 8 * 6 + 80, windowSize.y / 2 + 90));	
	
	
	
	// ============================== FOOT ============================== // 
	
	// "press enter to resume"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press enter to resume", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void PausedScene::unload() {
	
  _ents.list.clear();
	
}

void PausedScene::reload() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
/* 
	{ // background	
	auto background = makeEntity();
	auto b = background->addComponent<ShapeComponent>();
	b->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x, windowSize.y));
	b->getShape().setPosition(sf::Vector2f(0,0));
	b->getShape().setFillColor(sf::Color(72,62,55));
	}
	
	{// "story of nome"
	auto son = makeEntity();
	auto sn = son->addComponent<TextComponent>("The Story of Nome", "WorstveldSling.ttf");
	sn->setColor(sf::Color(200 , 190, 183));
	sn->setCharacterSize(75);
	sn->SetPosition({windowSize.x / 2 - sn->getText().getLocalBounds().width / 2, 10});
	}
	
	{ // ============================== CONTENT ============================== // 
	
	// "Preference Options"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Preference Options", "Rubik-Medium.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(50);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 200});
	
	}
	
	{ // ============================== DESCRIPTIONS & KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	makeDescription("Screen Resolution", sf::Vector2f(windowSize.x / 2 - 20, 290));	
	makeDescription("Full Screen",sf::Vector2f(windowSize.x / 2 - 20, 345));	
	makeDescription("Remap Controls", sf::Vector2f(windowSize.x / 2 - 20, 400));
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 305));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 360));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 415));
	
	makeKeyText("S", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 300));
	makeKeyText("F", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 355));
	makeKeyText("R", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 410));
	}
		
	{ // ============================== SCREEN MENU ============================== // 
	
	std::shared_ptr<sf::Texture> screenResSprites = Resources::get<sf::Texture>("ui_screen_res.png");
	std::shared_ptr<sf::Texture> fullScreenSprites = Resources::get<sf::Texture>("ui_fullscreen.png");
	
	// fullscreen indicator
	auto fsi = makeEntity();
	auto fsI = fsi->addComponent<ShapeComponent>();
	fsI->setShape<sf::RectangleShape>(sf::Vector2f(52, 40));
	fsI->getShape().setOrigin(Vector2f(20,20));
	fsI->getShape().setFillColor(sf::Color(255,255,255));
	fsI->setTexture(fullScreenSprites, sf::IntRect(0,0,52,40));
	fsI->getShape().setPosition(sf::Vector2f(windowSize.x / 2 + 80, 360));
	
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,0,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,33,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,66,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 102), screenResSprites, sf::IntRect(0,99,168,102), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 305));
	
	setSelectedResolution();
	
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,167,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 305));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,235,168,34), sf::Vector2f(windowSize.x / 2 + 80, 339));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,269,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	
	}
	
	{ // ============================== FOOT ============================== // 
	
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
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, 500));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	}
	 */
}


