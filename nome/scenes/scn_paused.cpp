

#include "../game.h"

using namespace sf;
using namespace std;



void PausedScene::update(const double& dt) {
	
	// resume game
	if ((Keyboard::isKeyPressed(Keyboard::Tab)) || (Joystick::isButtonPressed(0, 7))) //start
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&level1);
	}
	
	// quit game and destroy current level
	if ((Keyboard::isKeyPressed(Keyboard::Q)) || (Joystick::isButtonPressed(0, 1))) //circle
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		
		Engine::endGame();
		Engine::changeScene(&menu);
	}
	
	// go to save game scene
	if ((Keyboard::isKeyPressed(Keyboard::S)) || (Joystick::isButtonPressed(0, 2))) //square
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&save);
	}
}

void PausedScene::makeDescription(std::string t, sf::Vector2f p) {
	
	// write the description for one of the controls
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "Rubik-Medium.ttf");
	text->setColor(sf::Color(200 , 190, 183));
	text->setCharacterSize(25);
	
	text->SetPosition(p);
	
}

void PausedScene::makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p) {
		
	// create the background for one of the keys
	auto entity = makeEntity();
	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	shape->getShape().setOrigin(20,20);
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, sf::IntRect(0,0,40,40));
	shape->getShape().setPosition(p);	
	
}

void PausedScene::makeKeyText(std::string t, sf::Vector2f p) {
	
	// write the key text for one the keys
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "DroidSansMono.ttf");
	text->setOrigin(text->getText().getLocalBounds().width / 2, text->getText().getLocalBounds().height / 2);
	text->setColor(sf::Color(72,62,55));
	text->setCharacterSize(25);
	text->SetPosition(p);
}

/* delete?

void PausedScene::resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p) {
	
	
	auto entity = makeEntity();
	entity->setVisible(v);

	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(s);
	shape->getShape().setOrigin(Vector2f(20,20));
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, r);
	shape->getShape().setPosition(p);
	
	
	
} */

void PausedScene::load() {
	
	// create top section
	UIScene::load();

	// ============================== CONTENT ============================== // 
	
	// "Game Paused"
	auto gamePaused = makeEntity();
	auto paused = gamePaused->addComponent<TextComponent>("Game Paused", "WorstveldSling.ttf");
	paused->setColor(sf::Color(200 , 190, 183));
	paused->setCharacterSize(100);
	paused->SetPosition({windowSize.x / 2 - paused->getText().getLocalBounds().width / 2, 170});
	
	
	
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
	
	// tab to go back
	auto back = makeEntity();
	auto goBack = back->addComponent<TextComponent>("Press TAB to resume game", "WorstveldSling.ttf");
	goBack->setColor(sf::Color(200 , 190, 183));
	goBack->setCharacterSize(50);
	goBack->SetPosition({windowSize.x / 2 - goBack->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
}

void PausedScene::unload() {
	
  _ents.list.clear();
	
}

void PausedScene::reload() {}


