

#include "../game.h"

using namespace sf;
using namespace std;

std::vector<std::shared_ptr<Entity>> menuStates;
std::shared_ptr<Entity> menuState;


void OptionsScene::update(const double& dt) {
	
	if (!menuOpen) {
		if ((Keyboard::isKeyPressed(Keyboard::B)) || (Joystick::isButtonPressed(0, 1))) //circle
		{
			if (Engine::getLevel() != nullptr) {
				Engine::changeScene(Engine::getLevel());
			}
			else {
				Engine::changeScene(&menu);
			}
		}

		if ((Keyboard::isKeyPressed(Keyboard::R)) || (Joystick::isButtonPressed(0, 2))) //square
		{
			Engine::changeScene(&remap);
		}

		if ((Keyboard::isKeyPressed(Keyboard::S)) || (Joystick::isButtonPressed(0, 3))) //triangle
		{
			showResMenu();
			menuOpen = true;
		}
	} else {
		int x = 0;
		if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Joystick::isButtonPressed(0, 7))) //start
		{
			menuOpen = false;
			closeResMenu();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			updateResMenu(1, dt);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			updateResMenu(-1, dt);
		}
		if (Joystick::isButtonPressed(0, 3)) //triangle
		{
			updateResMenu(1, dt);
		}
	}
}

void OptionsScene::showResMenu() {
	
	for (auto &m : menuStates) {
		m->setVisible(false);
	}
	
	// show menu
	// switch selected position and intrect
	
	menuStates[3]->setVisible(true);
	menuStates[4]->setVisible(true);
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	if (windowSize.x == 800 && windowSize.y == 600) {
		
		auto shape = menuStates[4]->getComponents<ShapeComponent>();
		shape[0]->getShape().setPosition(Vector2f(windowSize.x / 2 + 80, 305));
		shape[0]->getShape().setTextureRect(IntRect(0,201,168,34));
	
	} else if (windowSize.x == 1024.f && windowSize.y == 768.f) {
		
		auto shape = menuStates[4]->getComponents<ShapeComponent>();
		shape[0]->getShape().setPosition(Vector2f(windowSize.x / 2 + 80, 339));
		shape[0]->getShape().setTextureRect(IntRect(0,235,168,34));
	
	} else if (windowSize.x == 1366.f && windowSize.y == 768.f) {
		
		auto shape = menuStates[4]->getComponents<ShapeComponent>();
		shape[0]->getShape().setPosition(Vector2f(windowSize.x / 2 + 80, 373));
		shape[0]->getShape().setTextureRect(IntRect(0,269,168,34));
	
	} 
}

void OptionsScene::preSelectResolution() {
	
	if (Renderer::getWindow().getSize().x == 800 && Renderer::getWindow().getSize().y == 600) {
		menuStates[0]->setVisible(true);
		menuState = menuStates[0];
	} else if (Renderer::getWindow().getSize().x == 1024 && Renderer::getWindow().getSize().y == 768) {
		menuStates[1]->setVisible(true);
		menuState = menuStates[1];
	} else if (Renderer::getWindow().getSize().x == 1366 && Renderer::getWindow().getSize().y == 768) {
		menuStates[2]->setVisible(true);
		menuState = menuStates[2];
	}  
	
}

void OptionsScene::closeResMenu() {
	
	for (auto &m : menuStates) {
		m->setVisible(false);
	}
	
	menuState->setVisible(true);
	
	if (menuState == menuStates[0]) {
		Renderer::getWindow().setSize(sf::Vector2u(800,600));
		// Renderer::getWindow().setView(sf::View(sf::FloatRect(0,0,800,600)));
	} else if (menuState == menuStates[1]) {
		Renderer::getWindow().setSize(sf::Vector2u(1024,768));
		// Renderer::getWindow().setView(sf::View(sf::FloatRect(0,0,1024,768)));
	} else if (menuState == menuStates[2]) {
		Renderer::getWindow().setSize(sf::Vector2u(1366,768));
		// Renderer::getWindow().setView(sf::View(sf::FloatRect(0,0,1366,768)));
	}
	
	preSelectResolution();
	
}

void OptionsScene::updateResMenu(int direction, const double& dt) {
	
	static double timer = 0.05f;
	timer -= dt;
	
	if (timer < 0) {
	
		sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
		
		auto shape = menuStates[4]->getComponents<ShapeComponent>();
		sf::Vector2f pos = shape[0]->getShape().getPosition();
		sf::IntRect intRect = IntRect(0,0,168,34);
			
		if (direction == 1) {
			
			if (pos.y == 305) {
				pos.y += 34;
				intRect.top = 235;
				menuState = menuStates[1];
			} else if (pos.y == 339) {
				pos.y += 34;
				intRect.top = 269;
				menuState = menuStates[2];
			} else  if (pos.y == 373) { //loop back round 
				pos.y -= 68;
				intRect.top = 201;
				menuState = menuStates[0];
			}
			
		} else {
			
			if (pos.y == 373) {
				pos.y -= 34;
				intRect.top = 235;
				menuState = menuStates[1];
			} else if (pos.y == 339) {
				pos.y -= 34;
				intRect.top = 201;
				menuState = menuStates[0];
			} else {
				intRect.top = 201;
			}
			
		}
		
		shape[0]->getShape().setPosition(pos);
		shape[0]->getShape().setTextureRect(intRect);
		
		timer = 0.05f;
		
	}		 
}

void OptionsScene::makeDescription(std::string t, sf::Vector2f p) {
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "Rubik-Medium.ttf");
	text->setColor(sf::Color(200 , 190, 183));
	text->setCharacterSize(25);
	
	p.x -= text->getText().getLocalBounds().width;
	text->SetPosition(p);
	
}

void OptionsScene::makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p) {
		
	auto entity = makeEntity();
	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	shape->getShape().setOrigin(20,20);
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, sf::IntRect(0,0,40,40));
	shape->getShape().setPosition(p);	
	
}

void OptionsScene::makeKeyText(std::string t, std::string f, sf::Color c, float s, sf::Vector2f p) {
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, f);
	text->setOrigin(text->getText().getLocalBounds().width / 2, text->getText().getLocalBounds().height / 2);
	text->setColor(c);
	text->setCharacterSize(s);
	text->SetPosition(p);
	
}

void OptionsScene::resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p) {
	
	auto entity = makeEntity();
	entity->setVisible(v);

	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(s);
	shape->getShape().setOrigin(Vector2f(20,20));
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, r);
	shape->getShape().setPosition(p);
	menuStates.push_back(entity);
	
	if (v) {
		menuState = entity;
	}
	
	
}

void OptionsScene::load() {
	
	UIScene::load();
	
	// ============================== CONTENT ============================== // 
	
	// "Preference Options"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Preference Options", "Rubik-Medium.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(50);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 200});
	
	
	// ============================== DESCRIPTIONS & KEYS ============================== // 
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	makeDescription("Screen Resolution", sf::Vector2f(windowSize.x / 2 - 20, 290));	
	makeDescription("Full Screen",sf::Vector2f(windowSize.x / 2 - 20, 340));	
	makeDescription("Remap Controls", sf::Vector2f(windowSize.x / 2 - 20, 390));
	makeDescription("Back", sf::Vector2f(windowSize.x / 2 - 20, 440));
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 305));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 355));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 405));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 455));
	
	makeKeyText("S", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 300));
	makeKeyText("F", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 350));
	makeKeyText("R", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 400));
	makeKeyText("B", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 450));
	
	
	
	// ============================== SCREEN CONTROLS ============================== // 
	
	std::shared_ptr<sf::Texture> screenResSprites = Resources::get<sf::Texture>("ui_screen_res.png");
	std::shared_ptr<sf::Texture> fullScreenSprites = Resources::get<sf::Texture>("ui_fullscreen.png");
	
	// fullscreen indicator
	auto fsi = makeEntity();
	auto fsI = fsi->addComponent<ShapeComponent>();
	fsI->setShape<sf::RectangleShape>(sf::Vector2f(52, 40));
	fsI->getShape().setOrigin(Vector2f(20,20));
	fsI->getShape().setFillColor(sf::Color(255,255,255));
	fsI->setTexture(fullScreenSprites, sf::IntRect(0,0,52,40));
	fsI->getShape().setPosition(sf::Vector2f(windowSize.x / 2 + 80, 355));
	
	// resolution indicators
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,0,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,33,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,66,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 102), screenResSprites, sf::IntRect(0,99,168,102), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 308));
	preSelectResolution();
	
}

void OptionsScene::unload() {
	
  _ents.list.clear();
  menuStates.clear();
  menuState = nullptr;
}
	
void OptionsScene::reload() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
/* 
	{ // background	
	auto background = makeEntity();
	auto b = background->addComponent<ShapeComponent>();
	b->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x, windowSize.y));
	b->getShape().setPosition(sf::Vector2f(0,0));
	b->getShape().setFillColor(sf::Color(72,62,55));
	}
	
	{// "story of nome"
	auto son = makeEntity();
	auto sn = son->addComponent<TextComponent>("The Story of Nome", "WorstveldSling.ttf");
	sn->setColor(sf::Color(200 , 190, 183));
	sn->setCharacterSize(75);
	sn->SetPosition({windowSize.x / 2 - sn->getText().getLocalBounds().width / 2, 10});
	}
	
	{ // ============================== CONTENT ============================== // 
	
	// "Preference Options"
	auto po = makeEntity();
	auto pO = po->addComponent<TextComponent>("Preference Options", "Rubik-Medium.ttf");
	pO->setColor(sf::Color(200 , 190, 183));
	pO->setCharacterSize(50);
	pO->SetPosition({windowSize.x / 2 - pO->getText().getLocalBounds().width / 2, 200});
	
	}
	
	{ // ============================== DESCRIPTIONS & KEYS ============================== // 
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	makeDescription("Screen Resolution", sf::Vector2f(windowSize.x / 2 - 20, 290));	
	makeDescription("Full Screen",sf::Vector2f(windowSize.x / 2 - 20, 345));	
	makeDescription("Remap Controls", sf::Vector2f(windowSize.x / 2 - 20, 400));
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 305));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 360));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 415));
	
	makeKeyText("S", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 300));
	makeKeyText("F", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 355));
	makeKeyText("R", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 410));
	}
		
	{ // ============================== SCREEN MENU ============================== // 
	
	std::shared_ptr<sf::Texture> screenResSprites = Resources::get<sf::Texture>("ui_screen_res.png");
	std::shared_ptr<sf::Texture> fullScreenSprites = Resources::get<sf::Texture>("ui_fullscreen.png");
	
	// fullscreen indicator
	auto fsi = makeEntity();
	auto fsI = fsi->addComponent<ShapeComponent>();
	fsI->setShape<sf::RectangleShape>(sf::Vector2f(52, 40));
	fsI->getShape().setOrigin(Vector2f(20,20));
	fsI->getShape().setFillColor(sf::Color(255,255,255));
	fsI->setTexture(fullScreenSprites, sf::IntRect(0,0,52,40));
	fsI->getShape().setPosition(sf::Vector2f(windowSize.x / 2 + 80, 360));
	
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,0,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,33,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,66,168,33), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 102), screenResSprites, sf::IntRect(0,99,168,102), sf::Vector2f(windowSize.x / 2 + 80, 305));
	resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 305));
	
	setSelectedResolution();
	
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,167,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 305));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,235,168,34), sf::Vector2f(windowSize.x / 2 + 80, 339));
	// resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,269,168,34), sf::Vector2f(windowSize.x / 2 + 80, 373));
	
	}
	
	{ // ============================== FOOT ============================== // 
	
	// "press enter to begin"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Press enter to begin", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(70);
	pe->SetPosition({windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, 490});
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	// line
	auto line2 = makeEntity();
	auto s2 = line->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, 500));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	}
	 */
}


