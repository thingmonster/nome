
#include "../game.h"

using namespace sf;
using namespace std;


void DeathScene::update(const double& dt) {
	
	// go to start menu
	if ((Keyboard::isKeyPressed(Keyboard::Tab)) || (Joystick::isButtonPressed(0, 7))) //start
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
	
	// create top section
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
	std::string deathMessage;
	if (Engine::getLevel()->getDeathCount() == 0) {
		deathMessage = "And you didn't kill any beetles";
	} else if (Engine::getLevel()->getDeathCount() == 1) {
		deathMessage = "But you killed a beetle!";
	} else {
		deathMessage = "But you killed "+deathCount+" beetles!";
	}
	auto beetleDeaths = makeEntity();
	auto deaths = beetleDeaths->addComponent<TextComponent>(deathMessage, "WorstveldSling.ttf");
	deaths->setColor(sf::Color(200 , 190, 183));
	deaths->setCharacterSize(40);
	deaths->SetPosition({windowSize.x / 2 - deaths->getText().getLocalBounds().width / 2, windowSize.y / 2});
	
	// "and you lasted HOW LONG!?"
	float lifespan = Engine::getLifespan();
	int precision = 2;
	if (lifespan >= 10) {
		precision = 0;
	}
	
	stringstream stream;
	stream << fixed << setprecision(precision) << lifespan;
	string yourLifeSpan = stream.str();
	
	std::string prefix;
	if (Engine::getLevel()->getDeathCount() == 0) {
		prefix = "But";
	} else {
		prefix = "And";
	}

	auto yourLife = makeEntity();
	auto tooYoung = yourLife->addComponent<TextComponent>(prefix+" you lasted a whole "+yourLifeSpan+" seconds!", "WorstveldSling.ttf");
	tooYoung->setColor(sf::Color(200 , 190, 183));
	tooYoung->setCharacterSize(40);
	tooYoung->SetPosition({windowSize.x / 2 - tooYoung->getText().getLocalBounds().width / 2, windowSize.y / 2 + 40});
	
	
	
	// ============================== FOOT ============================== // 
	
	// press tab
	auto pressEnter = makeEntity();
	auto toStartOver = pressEnter->addComponent<TextComponent>("Press TAB to go back to the start screen", "WorstveldSling.ttf");
	toStartOver->setColor(sf::Color(200 , 190, 183));
	toStartOver->setCharacterSize(50);
	toStartOver->SetPosition({windowSize.x / 2 - toStartOver->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
	// ============================== END GAME ============================== // 
	
	Engine::endGame();
}

void DeathScene::unload() {
	
  _ents.list.clear();
	
}

void DeathScene::reload() {
	
}
