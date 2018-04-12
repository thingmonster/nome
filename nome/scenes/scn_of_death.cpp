
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
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("You Died!!", "WorstveldSling.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(100);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 170});
	
	
		
	// ============================== FOOT ============================== // 
	
	// "press enter to start over"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press ENTER to go back to the start screen", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(40);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
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
