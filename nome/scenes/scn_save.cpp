
#include "../game.h"

using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> SaveScene::inputField;

void SaveScene::update(const double& dt) {
	
	// save game with the filename entered then resume
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
		if (userInput.length() > 0) {
			saveGame();
			Engine::setReadingInput(false);
			Engine::changeScene(&level1);
		}
	}
	
	// resume game
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
	
	// collect new user input and add to current filename
	userInput += Engine::getInput();
	auto text = userText->getComponents<TextComponent>();
	text[0]->setString(userInput);
	
	// move cursor
	auto shape = cursor->getComponents<ShapeComponent>();
	shape[0]->getShape().setPosition(Vector2f(
		windowSize.x / 2 - 132 + text[0]->getText().getLocalBounds().width, 
		windowSize.y - 247
	));
	
	// flash cursor
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
	
	// craete top section
	UIScene::load();
	
	// tell the engine to start reading input
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
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void SaveScene::unload() {
	
  _ents.list.clear();
	userInput = "";
	
}

void SaveScene::reload() {
	
}

void SaveScene::saveGame() {
	
	// get all entities and current level index
	std::vector<std::shared_ptr<Entity>> entities = Scene::getEntities();
	std::string gameString = "1"; // needs replaced with current level
	
	
	// determine positions of each entity relative to 
	// the map and assign a number between 0 and 1
	sf::Vector2f pos;
	for (auto& e : entities) {
		
		pos.x = (e->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize());
		pos.y = (e->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize());
		
		if (e->getTag().length() > 0) {
			gameString += "\n";
			gameString += e->getTag();
			gameString += ",";
			gameString += std::to_string(pos.x);
			gameString += ",";
			gameString += std::to_string(pos.y);
		}
	}
	
	// write level and entities to file
	ofstream gameFile;
	gameFile.open (userInput+".txt");
	gameFile << gameString;
	gameFile.close();
	
	// prepend filename to games list file contents
	ifstream savedGames ("games.txt");	
	string filenames = userInput;
	string filenamesString;
	if (savedGames.is_open()) {
		while (getline(savedGames, filenamesString)) {
			filenames += "\n"+filenamesString;
		}
		savedGames.close();
	} else {
		cout << "Unable to open file" << endl; 
	}
	
	// write new games list to file
	ofstream gamesList;
	gamesList.open ("games.txt");
	gamesList << filenames;
	gamesList.close();
	
}
		
		

