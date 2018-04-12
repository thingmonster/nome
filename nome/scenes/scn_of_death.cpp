
#include "../game.h"

using namespace sf;
using namespace std;


void DeathScene::update(const double& dt) {
	
	
	if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Joystick::isButtonPressed(0, 7))) //start
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			// do nothing
		}
		Engine::changeScene(&menu);
	}
	
}

void DeathScene::load() {
	
	UIScene::load();
	
	// ============================== CONTENT ============================== // 
	
	// "You died"
	auto youDied = makeEntity();
	auto deadItellYou = youDied->addComponent<TextComponent>("You Died!!", "WorstveldSling.ttf");
	deadItellYou->setColor(sf::Color(200 , 190, 183));
	deadItellYou->setCharacterSize(100);
	deadItellYou->SetPosition({windowSize.x / 2 - deadItellYou->getText().getLocalBounds().width / 2, 170});
		
	// "but you killed HOW MANY beetles!?"
	std::string deathCount = std::to_string(Engine::getLevel()->getDeathCount());
	auto beetleDeaths = makeEntity();
	auto deaths = beetleDeaths->addComponent<TextComponent>("But you killed "+deathCount+" beetles!", "WorstveldSling.ttf");
	deaths->setColor(sf::Color(200 , 190, 183));
	deaths->setCharacterSize(40);
	deaths->SetPosition({windowSize.x / 2 - deaths->getText().getLocalBounds().width / 2, windowSize.y / 2});
	
	
	
	// ============================== FOOT ============================== // 
	
	// "press enter to start over"
	auto pressEnter = makeEntity();
	auto toStartOver = pressEnter->addComponent<TextComponent>("Press ENTER to go back to the start screen", "WorstveldSling.ttf");
	toStartOver->setColor(sf::Color(200 , 190, 183));
	toStartOver->setCharacterSize(40);
	toStartOver->SetPosition({windowSize.x / 2 - toStartOver->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void DeathScene::unload() {
	
  _ents.list.clear();
	
}

void DeathScene::reload() {
	
}
