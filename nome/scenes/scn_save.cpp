
#include "../game.h"

using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> SaveScene::inputField;

void SaveScene::update(const double& dt) {
	
	
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		saveGame();
		Engine::setReadingInput(false);
		Engine::changeScene(&level1);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
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
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Save Game", "WorstveldSling.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(100);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 170});
	
	
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
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press ENTER to resume", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 135});
	
	//  C to cancel
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

void SaveScene::unload() {
	
  _ents.list.clear();
	
}

void SaveScene::reload() {
	
}

void SaveScene::saveGame() {
	
	std::vector<std::shared_ptr<Entity>> entities = Scene::getEntities();
	std::string str = "1";
	
	for (auto& e : entities) {
		str += "\n";
		str += std::to_string(e->getPosition().x);
		str += ",";
		str += std::to_string(e->getPosition().y);
	}
	
	ofstream myfiles;
	myfiles.open ("test.txt");
	myfiles << str;
	myfiles.close();
	
}
		
		

