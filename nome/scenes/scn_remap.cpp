
#include "scn_remap.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void RemapScene::update(const double& dt) {
	
	Event event;
	while (Renderer::getWindow().pollEvent(event)) {
		cout << "hi" ;
		if (event.type == sf::Event::EventType::KeyPressed){
				cout << event.key.code << endl;
		}
	}
	 
	if (Keyboard::isKeyPressed(Keyboard::L)) {
		Engine::controls[0] = Keyboard::L;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::B)) {
		Engine::changeScene(&menu);			
	}
	
}

void RemapScene::load() {
	
	cout << Engine::controls.size() << endl;
	Engine::controls.clear();
	cout << Engine::controls.size() << endl;
	
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
	
	
	// ============================== CONTENT ============================== // 
	
	// "Remap Controls"
	auto rm = makeEntity();
	auto rM = rm->addComponent<TextComponent>("Remap Controls", "Rubik-Medium.ttf");
	rM->setColor(sf::Color(200 , 190, 183));
	rM->setCharacterSize(50);
	rM->SetPosition({windowSize.x / 2 - rM->getText().getLocalBounds().width / 2, 200});
	
	/* // ============================== DESCRIPTIONS & KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	makeDescription("Screen Resolution", sf::Vector2f(windowSize.x / 2 - 20, 290));	
	makeDescription("Full Screen",sf::Vector2f(windowSize.x / 2 - 20, 340));	
	makeDescription("Remap Controls", sf::Vector2f(windowSize.x / 2 - 20, 390));
	makeDescription("Back to Start Screen", sf::Vector2f(windowSize.x / 2 - 20, 440));
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 305));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 355));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 405));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 455));
	
	makeKeyText("S", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 300));
	makeKeyText("F", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 350));
	makeKeyText("R", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 400));
	makeKeyText("B", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 450));
	 */
	
	/* // ============================== SCREEN MENUS ============================== // 
	
	
	
	std::shared_ptr<sf::Texture> screenResSprites = Resources::get<sf::Texture>("ui_screen_res.png");
	std::shared_ptr<sf::Texture> fullScreenSprites = Resources::get<sf::Texture>("ui_fullscreen.png");
	
	// fullscreen indicator
	auto fsi = makeEntity();
	auto fsI = fsi->addComponent<ShapeComponent>();
	fsI->setShape<sf::RectangleShape>(sf::Vector2f(52, 40));
	fsI->getShape().setOrigin(Vector2f(20,20));
	fsI->getShape().setFillColor(sf::Color(255,255,255));
	fsI->setTexture(fullScreenSprites, sf::IntRect(0,0,52,40));
	fsI->getShape().setPosition(sf::Vector2f(windowSize.x / 2 + 80, 355));
	
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,0,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,33,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,66,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 102), screenResSprites, sf::IntRect(0,99,168,102), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 308));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,167,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 305));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,235,168,34), sf::Vector2f(windowSize.x / 2 + 80, 339));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,269,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	preSelectResolution();
	 */
	
	// ============================== FOOT ============================== // 
	
	// "press enter to begin"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press enter to begin", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, 485});
	
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

void RemapScene::reload() {

}


