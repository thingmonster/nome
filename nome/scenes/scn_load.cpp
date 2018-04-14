
#include "../game.h"

using namespace sf;
using namespace std;


void LoadScene::update(const double& dt) {
	
	static double timer = 0.f;
	timer -= dt;
	
	
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
	
	levels.push_back(&level1);
	
	UIScene::load();
	
	// ============================== CONTENT ============================== // 
	
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
	
	std::string message;
	if (gamesExist) {
		message = "Up and Down to select, Enter to load game";
	} else {
		message = "Sorry, no one has saved any games yet";
	}
	
	// "Load Game"
	auto loadGame = makeEntity();
	auto load = loadGame->addComponent<TextComponent>(message, "WorstveldSling.ttf");
	load->setColor(sf::Color(200 , 190, 183));
	load->setCharacterSize(50);
	load->SetPosition({windowSize.x / 2 - load->getText().getLocalBounds().width / 2, 170});
	
	
	
	
	if (filenames.size() > 0) {
	
		highlight = makeEntity();
		auto background = highlight->addComponent<ShapeComponent>();
		background->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 300, 40));
		background->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 - 3));
		background->getShape().setFillColor(sf::Color(90 , 80, 75));
		background->getShape().setOrigin(Vector2f((windowSize.x - 300) / 2, 20));
	}
	
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
	
	// Tab to cancel
	
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
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 105));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void LoadScene::unload() {
	
  _ents.list.clear();
	
}

void LoadScene::reload() {
	
}

void LoadScene::loadGame() {
	
	int line = 1;
	int level = -1;
	std::string entity;
	std::vector<std::shared_ptr<Entity>> entities;
	
	ifstream savedGame (filenames[highlightPosition]+".txt");
	
	string str;
	if (savedGame.is_open()) {
		while (getline(savedGame, str)) {
			if (line == 1) {
				level = std::stoi(str) - 1;
				line = 2;
			} else {
				entities.push_back(loadEntity(str));
			}
		}
		savedGame.close();
	} else {
		cout << "Unable to open file" << endl; 
	}
	
	if (level >= 0) {
		Engine::changeLevel(levels[level]);
		Engine::restoreGame(entities);
	} else {
		cout << "no content in file" << endl;
	}
}

std::shared_ptr<Entity> LoadScene::loadEntity(std::string s) {
	
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
