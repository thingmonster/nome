
#include "../game.h"

using namespace sf;
using namespace std;


void LoadScene::update(const double& dt) {
	
	// prevent single key presses registering multiple times
	static double timer = 0.f;
	timer -= dt;
	
	// load the selected game
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
		loadGame();
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

		if (Engine::getLevel() != nullptr) {
			Engine::changeScene(Engine::getLevel());
		} else {
			Engine::changeScene(&menu);
		}
	}	
	
	// move selected game highlight up the menu
	if ((Keyboard::isKeyPressed(Keyboard::Up)) /* need ps4 controls! */ )
	{
		if (timer < 0) {
			highlightPosition--;
			auto shape = highlight->getComponents<ShapeComponent>();
			Vector2f pos = shape[0]->getShape().getPosition();
			if (pos.y > windowSize.y / 2 - 3) {
				pos.y -= 50;
			}
			shape[0]->getShape().setPosition(pos);
			timer = .12f;
		}
	}
	
	
	// move selected game highlight down the menu
	if ((Keyboard::isKeyPressed(Keyboard::Down)) /* need ps4 controls! */ )
	{
		if (timer < 0) {
			highlightPosition++;
			auto shape = highlight->getComponents<ShapeComponent>();
			Vector2f pos = shape[0]->getShape().getPosition();
			if (pos.y < windowSize.y / 2 - 3 + ((filenames.size() - 1) * 50)) {
				pos.y += 50;
			}
			shape[0]->getShape().setPosition(pos);
			timer = .12f;
		}
	}	
}

void LoadScene::load() {
	
	// more levels would need to be added here unless stored elsewhere
	levels.push_back(&level1); 
	
	// create top section
	UIScene::load();
	
	// ============================== CONTENT ============================== // 
	
	// check any saved games exist
	
	bool gamesExist = false;
	
	ifstream savedGames ("games.txt");
	
	string str;
	if (savedGames.is_open()) {
		while (getline(savedGames, str)) {
			if (filenames.size() < 4) {
				filenames.push_back(str);
				gamesExist = true;
			}
		}
		savedGames.close();
	} else {
		cout << "Unable to open file" << endl; 
	}
	
	// customise message
	std::string message;
	if (gamesExist) {
		message = "Up and Down to select, Enter to load game";
	} else {
		message = "Sorry, no one has saved any games yet";
	}
	
	// "Load Game" text
	auto loadGame = makeEntity();
	auto load = loadGame->addComponent<TextComponent>(message, "WorstveldSling.ttf");
	load->setColor(sf::Color(200 , 190, 183));
	load->setCharacterSize(50);
	load->SetPosition({windowSize.x / 2 - load->getText().getLocalBounds().width / 2, 170});
	
	
	
	// if there's at least one game create the highlight
	if (filenames.size() > 0) {
	
		highlight = makeEntity();
		auto background = highlight->addComponent<ShapeComponent>();
		background->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 300, 40));
		background->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 - 3));
		background->getShape().setFillColor(sf::Color(90 , 80, 75));
		background->getShape().setOrigin(Vector2f((windowSize.x - 300) / 2, 20));
	}
	
	// create entities to display the text for up to four saved games
	for (int i = 0; i < filenames.size(); i++) {
		
		auto game = makeEntity();
		auto text = game->addComponent<TextComponent>(filenames[i], "DroidSansMono.ttf");
		text->setColor(sf::Color(200 , 190, 183));
		text->setCharacterSize(25);
		text->SetPosition({
			windowSize.x / 2 - text->getText().getLocalBounds().width / 2, 
			windowSize.y / 2 - 20 + (50 * i)
		});
		
		fileEntities.push_back(game);
	}
	
	
		
	// ============================== FOOT ============================== // 
	
	// check whether a game is in progress for customised message
	
	std::string backText;
	if (Engine::getLevel() == nullptr) {
		backText = "Press TAB to cancel and go back";
	} else {
		backText = "Press TAB to cancel and resume game";
	}
	
	auto cancel = makeEntity();
	auto goBack = cancel->addComponent<TextComponent>(backText, "WorstveldSling.ttf");
	goBack->setColor(sf::Color(200 , 190, 183));
	goBack->setCharacterSize(50);
	goBack->SetPosition({windowSize.x / 2 - goBack->getText().getLocalBounds().width / 2, windowSize.y - 85});
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 105));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void LoadScene::unload() {
	
  _ents.list.clear();
	
}

void LoadScene::reload() {
	
}

void LoadScene::loadGame() {
	
	/*
	
	load game from the file that corresponds 
	with the highlight position
	
	*/
	
	int line = 1;
	int level = -1;
	std::string entity;
	std::vector<std::shared_ptr<Entity>> entities;
	
	ifstream savedGame (filenames[highlightPosition]+".txt");
	string str;
	
	// iterate over each line
	if (savedGame.is_open()) {
		while (getline(savedGame, str)) {
			if (line == 1) {
				// fist line stores the level number
				level = std::stoi(str) - 1;
				line = 2;
			} else {
				// subsequent lines store entities
				entities.push_back(loadEntity(str));
			}
		}
		savedGame.close();
	} else {
		cout << "Unable to open file" << endl; 
	}
	
	// if this is a valid file go to game
	if (level >= 0) {
		Engine::changeLevel(levels[level]);
		Engine::restoreGame(entities);
	} else {
		cout << "no content in file" << endl;
	}
}

std::shared_ptr<Entity> LoadScene::loadEntity(std::string s) {
	
	/*
	
	split a line from the file into its tokens
	(tag, position x, position y) and use them to 
	create a pre-positioned entity
	
	positions are relative to the map size and are
	stored as numbers between 0 and 1 - these are converted 
	to screen coordinates in the level scene's restore
	method
	
	*/
	
	std::string delimiter = ",";

	size_t pos = 0;
	vector<std::string> tokens;
	std::string token;
	
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);
	
	sf::Vector2f p(stof(tokens[1]),stof(tokens[2]));
	
	auto e = make_shared<Entity>(this, tokens[0], p);
	
	return e;
}
