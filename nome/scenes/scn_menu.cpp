
#include "../game.h"

using namespace sf;
using namespace std;

const std::string controls[] = {
    "Left",
    "Right",
    "Up",
    "Down"
};



void MenuScene::update(const double& dt) {
	
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		Engine::changeScene(&level1);
		
	}
	
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		Engine::changeScene(&options);
		
	}
	
	if (Keyboard::isKeyPressed(Keyboard::L)) {
		Engine::changeScene(&loadGame);
	}
	
}

void MenuScene::buildKeys() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	// down
	
	sf::Vector2f kPos = Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 + 30);
	sf::Vector2f dPos = Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 + 60);
		
	if ((Engine::controls[0] > 70) && (Engine::controls[0] < 75)) {		
		textureKey(3, kPos, dPos);	
	} else {
		textKey(3, kPos, dPos, 0);	
	}
	
	// left
	
	kPos = Vector2f(windowSize.x  / 2 + 70, windowSize.y / 2 - 20);
	dPos = Vector2f(windowSize.x  / 2 + 10, windowSize.y / 2 - 30);
		
	if ((Engine::controls[0] > 70) && (Engine::controls[0] < 75)) {		
		textureKey(0, kPos, dPos);	
	} else {
		textKey(0, kPos, dPos, -1);	
	}
	
	// right
	
	kPos = Vector2f(windowSize.x  / 2 + 130, windowSize.y / 2 - 20);
	dPos = Vector2f(windowSize.x  / 2 + 190, windowSize.y / 2 - 30);
		
	if ((Engine::controls[0] > 70) && (Engine::controls[0] < 75)) {		
		textureKey(1, kPos, dPos);	
	} else {
		textKey(1, kPos, dPos, 1);	
	}
	
	// up
	
	kPos = Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 - 70);
	dPos = Vector2f(windowSize.x  / 2 + 100, windowSize.y / 2 - 135);
		
	if ((Engine::controls[2] > 70) && (Engine::controls[2] < 75)) {		
		textureKey(2, kPos, dPos);
	} else {
		textKey(2, kPos, dPos, 0);
	}
	
	
	
}

void MenuScene::textureKey(int c, sf::Vector2f kPos, sf::Vector2f dPos) {

	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	IntRect ir;
	
	if (Engine::keyStrings[Engine::controls[c]] == "Left") {
		ir = IntRect(120,0,40,40);
	} else if (Engine::keyStrings[Engine::controls[c]] == "Right") {
		ir = IntRect(160,0,40,40);
	} else if (Engine::keyStrings[Engine::controls[c]] == "Up") {
		ir = IntRect(200,0,40,40);
	} else if (Engine::keyStrings[Engine::controls[c]] == "Down") {
		ir = IntRect(240,0,40,40);
	}
		
		
		
	// background
	auto entity = makeEntity();
	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	shape->getShape().setOrigin(Vector2f(20,20));
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(keySprites, ir);
	shape->getShape().setPosition(kPos);
	
	// control description
	auto description = makeEntity();
	auto text = description->addComponent<TextComponent>(controls[c], "WorstveldSling.ttf");
	text->setOrigin(text->getText().getLocalBounds().width / 2, text->getText().getLocalBounds().height / 2);
	text->setColor(sf::Color(200 , 190, 183));
	text->setCharacterSize(40);
	text->SetPosition(Vector2f(dPos.x - 4, dPos.y));
	
}

void MenuScene::textKey(int c, sf::Vector2f kPos, sf::Vector2f dPos, int direction) {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// description
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(controls[c], "WorstveldSling.ttf");
	text->setOrigin(
		text->getText().getLocalBounds().width / 2 - ((text->getText().getLocalBounds().width / 2) - 10) * direction, 
		text->getText().getLocalBounds().height / 2
	);
	text->setColor(sf::Color(200, 190, 183));
	text->setCharacterSize(40);
	text->SetPosition(dPos);
	
		
		
		
		
	// key text
	auto key = makeEntity();
	auto keyText = key->addComponent<TextComponent>(Engine::keyStrings[Engine::controls[c]], "Rubik-Medium.ttf");
	keyText->setOrigin(
		keyText->getText().getLocalBounds().width / 2 - (keyText->getText().getLocalBounds().width / 2 * direction),
		keyText->getText().getLocalBounds().height / 2
	);
	keyText->setColor(sf::Color(72,62,55));
	keyText->setCharacterSize(25);
	keyText->SetPosition(Vector2f(
		kPos.x - (10 * direction), 
		kPos.y
	));
	
	
	// calculate bounds for background
	
	Vector2f bounds(keyText->getText().getLocalBounds().width, 40);
	
	IntRect textureRect(0,0,40,40);
	if (bounds.x > 80) {
		textureRect = IntRect(40,0,80,40);
	}
	
	if (bounds.x < 20) {
		bounds.x = 40;
	} else {
		bounds.x += 20;
	}
	
	
	
	// background
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	auto background = makeEntity();
	auto bg = background->addComponent<ShapeComponent>();
	bg->setShape<sf::RectangleShape>(bounds);
	bg->getShape().setOrigin(Vector2f(
		bounds.x / 2 - (bounds.x / 2 * direction),
		10
	));
	bg->getShape().setFillColor(sf::Color(255,255,255));
	bg->setTexture(keySprites, textureRect);
	bg->getShape().setPosition(Vector2f(
		kPos.x - (20 * direction), 
		kPos.y - 6
	));
	
	
	// update position of descriptors depending on button size
	
	text->SetPosition(Vector2f(
		dPos.x + (keyText->getText().getLocalBounds().width - 10)* direction, 
		dPos.y
	));
	
	// move text in front of button background
	
	iter_swap(_ents.list.begin() + _ents.list.size() - 2, _ents.list.begin() + _ents.list.size() - 1);
	
}

void MenuScene::load() {
	
	UIScene::load();
	
	// ============================== KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	
	// options key background
	auto okb = makeEntity();
	auto ob = okb->addComponent<ShapeComponent>();
	ob->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	ob->getShape().setOrigin(Vector2f(20,20));
	ob->getShape().setFillColor(sf::Color(255,255,255));
	ob->setTexture(keySprites, sf::IntRect(0,0,40,40));
	ob->getShape().setPosition(sf::Vector2f(100, 180));
	
	// options key text
	auto oslO = makeEntity();
	auto o = oslO->addComponent<TextComponent>("O", "DroidSansMono.ttf");
	o->setOrigin(o->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	o->setColor(sf::Color(72,62,55));
	o->setCharacterSize(25);
	o->SetPosition({100, 175});
	
	// options key description
	auto oslOptions = makeEntity();
	auto options = oslOptions->addComponent<TextComponent>("Options", "WorstveldSling.ttf");
	options->setOrigin(options->getText().getLocalBounds().width / 2, o->getText().getLocalBounds().height / 2);
	options->setColor(sf::Color(200 , 190, 183));
	options->setCharacterSize(40);
	options->SetPosition({165, 162});
	
	
	// ============================== CONTROLS ============================== // 
	
	buildKeys();
	
	// ============================== FOOT ============================== // 
	
	// "use the ball to kill the beetles"
	auto ubkb = makeEntity();
	auto ub = ubkb->addComponent<TextComponent>("Use the ball to kill the beetles", "WorstveldSling.ttf");
	ub->setColor(sf::Color(200 , 190, 183));
	ub->setCharacterSize(35);
	ub->SetPosition({windowSize.x / 2 - ub->getText().getLocalBounds().width / 2, windowSize.y - 150});
	
	// "rest is up to you"
	auto riuty = makeEntity();
	auto ri = riuty->addComponent<TextComponent>("The rest is up to you...", "WorstveldSling.ttf");
	ri->setColor(sf::Color(200 , 190, 183));
	ri->setCharacterSize(25);
	ri->SetPosition({windowSize.x / 2 - ri->getText().getLocalBounds().width / 2, windowSize.y - 120});
	
	// "press enter to begin"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press enter to begin", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, windowSize.y - 110});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 150));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
}

void MenuScene::unload() {
	
  _ents.list.clear();
	
	
}

void MenuScene::reload() {
	
	
}






