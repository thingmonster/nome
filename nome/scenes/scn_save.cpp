
#include "../game.h"

using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> SaveScene::inputField;

void SaveScene::update(const double& dt) {
	
	
	if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Joystick::isButtonPressed(0, 7))) //start
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		saveGame();
		Engine::setReadingInput(false);
		Engine::changeScene(&level1);
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::Tab)) || (Joystick::isButtonPressed(0, 1))) //circle
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::setReadingInput(false);
		Engine::changeScene(&level1);
	}
	
	userInput += Engine::getInput();
	
	auto text = userText->getComponents<TextComponent>();
	text[0]->setString(userInput);
	
	auto shape = cursor->getComponents<ShapeComponent>();
	shape[0]->getShape().setPosition(Vector2f(
		windowSize.x / 2 - 135 + text[0]->getText().getLocalBounds().width, 
		windowSize.y - 247
	));
	
	static double timer = 0.5f;
	timer -= dt;
	if (timer < 0.f)  {
		if (cursor->getVisible()) {
			cursor->setVisible(false);
		} else {
			cursor->setVisible(true);
		}
		timer = 0.5f;
	}
}

void SaveScene::load() {
	
	UIScene::load();
	
	Engine::setReadingInput(true);
	
	
	// ============================== CONTENT ============================== // 
	
	// "Save Game"
	auto saveGame = makeEntity();
	auto save = saveGame->addComponent<TextComponent>("Save Game", "WorstveldSling.ttf");
	save->setColor(sf::Color(200 , 190, 183));
	save->setCharacterSize(100);
	save->SetPosition({windowSize.x / 2 - save->getText().getLocalBounds().width / 2, 170});
	
	
	// input field
	inputField = Resources::get<sf::Texture>("ui_input.png");
	auto input = makeEntity();
	auto inputshape = input->addComponent<ShapeComponent>();
	inputshape->setShape<sf::RectangleShape>(sf::Vector2f(300,40));
	inputshape->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 235));
	inputshape->getShape().setOrigin(Vector2f(150,20));
	inputshape->setTexture(inputField, sf::IntRect(0,0,300,40));
	
	// cursor
	cursor = makeEntity();
	auto cursorshape = cursor->addComponent<ShapeComponent>();
	cursorshape->setShape<sf::RectangleShape>(sf::Vector2f(2,25));
	cursorshape->getShape().setPosition(sf::Vector2f(windowSize.x / 2 - 135, windowSize.y - 247));
	cursorshape->getShape().setOrigin(Vector2f(1,0));
		
	// User Input
	userText = makeEntity();
	auto inputText = userText->addComponent<TextComponent>("", "DroidSansMono.ttf");
	inputText->setColor(sf::Color(200 , 190, 183));
	inputText->setCharacterSize(25);
	inputText->SetPosition(sf::Vector2f(windowSize.x / 2 - 140, windowSize.y - 250));
	
		
	// ============================== FOOT ============================== // 
	
	// "press enter to resume"
	
	auto pressEnter = makeEntity();
	auto enter = pressEnter->addComponent<TextComponent>("Press ENTER to save and resume", "WorstveldSling.ttf");
	enter->setColor(sf::Color(200 , 190, 183));
	enter->setCharacterSize(60);
	enter->SetPosition({windowSize.x / 2 - enter->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	//  tab to cancel
	auto back = makeEntity();
	auto goBack = back->addComponent<TextComponent>("or TAB to cancel and resume", "WorstveldSling.ttf");
	goBack->setColor(sf::Color(200 , 190, 183));
	goBack->setCharacterSize(40);
	goBack->SetPosition({windowSize.x / 2 - goBack->getText().getLocalBounds().width / 4, windowSize.y - 70});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void SaveScene::unload() {
	
  _ents.list.clear();
	
}

void SaveScene::reload() {
	
}

void SaveScene::saveGame() {
	
	std::vector<std::shared_ptr<Entity>> entities = Scene::getEntities();
	std::string str = "1"; // needs replaced with current level
	sf::Vector2f pos;
	
	for (auto& e : entities) {
		
		pos.x = (e->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize());
		pos.y = (e->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize());
		
		if (e->getTag().length() > 0) {
			str += "\n";
			str += e->getTag();
			str += ",";
			str += std::to_string(pos.x);
			str += ",";
			str += std::to_string(pos.y);
		}
	}
	
	ofstream myfiles;
	myfiles.open ("test.txt");
	myfiles << str;
	myfiles.close();
	
}
		
		

