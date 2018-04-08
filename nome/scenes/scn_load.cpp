
#include "../game.h"

using namespace sf;
using namespace std;


void LoadScene::update(const double& dt) {
	
	
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		loadGame();
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		if (Engine::getLevel() != nullptr) {
			Engine::changeScene(Engine::getLevel());
		} else {
			Engine::changeScene(&menu);
		}
	}
	
}

void LoadScene::load() {
	
	levels.push_back(&level1);
	
	UIScene::load();
	
	// ============================== CONTENT ============================== // 
	
	// "Load Game"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Load Game", "WorstveldSling.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(100);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 170});
	
	
		
	// ============================== FOOT ============================== // 
	
	// "press enter to resume"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press ENTER to resume", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	//  Tab to cancel
	auto cr = makeEntity();
	auto c = cr->addComponent<TextComponent>("or TAB to cancel and go back", "WorstveldSling.ttf");
	c->setColor(sf::Color(200 , 190, 183));
	c->setCharacterSize(40);
	c->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 4, windowSize.y - 70});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 165));
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
	
	ifstream savedGame ("test.txt");
	
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
	
	cout << "esize " << entities.size() << endl;
	
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
	
	sf::Vector2f p(stof(tokens[0]),stof(tokens[1]));
	
	p.x = (p.x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x;
	p.y = (p.y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y;
	
	auto e = make_shared<Entity>(this, p);
	return e;
}
