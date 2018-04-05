
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
	
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		cout << "o" << endl;
		Engine::changeScene(&options);
		
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
	
	
	// ============================== KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> enemySprites = Resources::get<sf::Texture>("ui_key.png");
	
	
	// options key background
	auto okb = makeEntity();
	auto ob = okb->addComponent<ShapeComponent>();
	ob->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	ob->getShape().setOrigin(Vector2f(20,20));
	ob->getShape().setFillColor(sf::Color(255,255,255));
	ob->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	ob->getShape().setPosition(sf::Vector2f(100, 180));
	
	// options key text
	auto oslO = makeEntity();
	auto o = oslO->addComponent<TextComponent>("O", "DroidSansMono.ttf");
	o->setOrigin(o->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	o->setColor(sf::Color(72,62,55));
	o->setCharacterSize(25);
	o->SetPosition({100, 175});
	
	// options key description
	auto oslOptions = makeEntity();
	auto options = oslOptions->addComponent<TextComponent>("Options", "WorstveldSling.ttf");
	options->setOrigin(options->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	options->setColor(sf::Color(200 , 190, 183));
	options->setCharacterSize(40);
	options->SetPosition({165, 165});
	
	
	
	// up arrow background
	auto uab = makeEntity();
	auto ua = uab->addComponent<ShapeComponent>();
	ua->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	ua->getShape().setOrigin(Vector2f(20,20));
	ua->getShape().setFillColor(sf::Color(255,255,255));
	ua->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	ua->getShape().setPosition(sf::Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 - 50));
	
	// up arrow key description
	auto uad = makeEntity();
	auto uaD = uad->addComponent<TextComponent>("forwards", "WorstveldSling.ttf");
	uaD->setOrigin(uaD->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	uaD->setColor(sf::Color(200 , 190, 183));
	uaD->setCharacterSize(40);
	uaD->SetPosition({windowSize.x / 2 + 100, windowSize.y / 2 - 130});
	
	// down arrow background
	auto dab = makeEntity();
	auto daB = dab->addComponent<ShapeComponent>();
	daB->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	daB->getShape().setOrigin(Vector2f(20,20));
	daB->getShape().setFillColor(sf::Color(255,255,255));
	daB->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	daB->getShape().setPosition(sf::Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 - 0));
	
	// down arrow key description
	auto dad = makeEntity();
	auto daD = dad->addComponent<TextComponent>("backwards", "WorstveldSling.ttf");
	daD->setOrigin(daD->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	daD->setColor(sf::Color(200 , 190, 183));
	daD->setCharacterSize(40);
	daD->SetPosition({windowSize.x / 2 + 100, windowSize.y / 2 + 30});
	
	// left arrow background
	auto lab = makeEntity();
	auto laB = lab->addComponent<ShapeComponent>();
	laB->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	laB->getShape().setOrigin(Vector2f(20,20));
	laB->getShape().setFillColor(sf::Color(255,255,255));
	laB->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	laB->getShape().setPosition(sf::Vector2f(windowSize.x  / 2 + 50, windowSize.y / 2 - 0));
	
	// left arrow key description
	auto lad = makeEntity();
	auto laD = lad->addComponent<TextComponent>("left", "WorstveldSling.ttf");
	laD->setOrigin(options->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	laD->setColor(sf::Color(200 , 190, 183));
	laD->setCharacterSize(40);
	laD->SetPosition({windowSize.x / 2 + 10, windowSize.y / 2 - 20});
	
	// right arrow background
	auto rab = makeEntity();
	auto raB = rab->addComponent<ShapeComponent>();
	raB->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	raB->getShape().setOrigin(Vector2f(20,20));
	raB->getShape().setFillColor(sf::Color(255,255,255));
	raB->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	raB->getShape().setPosition(sf::Vector2f(windowSize.x  / 2 + 150, windowSize.y / 2 - 0));
	
	// right arrow key description
	auto rad = makeEntity();
	auto raD = rad->addComponent<TextComponent>("right", "WorstveldSling.ttf");
	raD->setOrigin(options->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	raD->setColor(sf::Color(200 , 190, 183));
	raD->setCharacterSize(40);
	raD->SetPosition({windowSize.x / 2 + 240, windowSize.y / 2 - 20});
	
	
	
	
	// ============================== FOOT ============================== // 
	
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
	// auto txt = makeEntity();
	// auto t = txt->addComponent<TextComponent>("Game Engine Skeleton", "Rubik-Medium.ttf");
	// t->setColor(sf::Color(200 , 190, 183));
	// t->setCharacterSize(50);
	// t->SetPosition({windowSize.x / 2 - t->getText().getLocalBounds().width / 2, 220});
	
	
}

void MenuScene::reload() {
	
	
}






