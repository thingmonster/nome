

#include "../game.h"

using namespace sf;
using namespace std;

// to store potential menu states and the menu state that is currently visible
std::vector<std::shared_ptr<Entity>> menuStates;
std::shared_ptr<Entity> menuState;


void OptionsScene::update(const double& dt) {

	// if the screen res menu has not been opened
	if (!menuOpen) {
		
		// resume game or go back to start menu
		if ((Keyboard::isKeyPressed(Keyboard::Tab)) || (Joystick::isButtonPressed(0, 1))) //circle
		{
			// play audio
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
			}
			else {
				if (Engine::getLevel() == nullptr) {
					Engine::changeScene(&menu);
				} else {
					Engine::changeScene(Engine::getLevel());
				}
			}
		}

		// go to remap scene
		if ((Keyboard::isKeyPressed(Keyboard::R)) || (Joystick::isButtonPressed(0, 2))) //square
		{
			// play audio
			auto jukebox = makeEntity();
			auto audio = jukebox->addComponent<AudioComponent>();
			audio->LoadAudio("Enter_Press.wav");
			audio->PlayAudio();
			while (audio->AudioIsPlaying())
			{
				//do nothing
			}
			Engine::changeScene(&remap);
		}

		// toggle fullscreen window mode and update indicator
		if (((Keyboard::isKeyPressed(Keyboard::F))) || (Joystick::isButtonPressed(0, 8))) //l3
		{
			// play audio
			auto jukebox = makeEntity();
			auto audio = jukebox->addComponent<AudioComponent>();
			audio->LoadAudio("Enter_Press.wav");
			audio->PlayAudio();
			while (audio->AudioIsPlaying())
			{
				//do nothing
			}
			Engine::changeMode();
			
			auto shape = fullscreenIndicator->getComponents<ShapeComponent>();
			if (Engine::getMode() == "fullscreen") {
				shape[0]->getShape().setTextureRect(IntRect(0,0,52,40));
			} else {
				shape[0]->getShape().setTextureRect(IntRect(52,0,52,40));
			}
		}

		// open screen resolution menu
		if ((Keyboard::isKeyPressed(Keyboard::S)) || (Joystick::isButtonPressed(0, 3))) //triangle
		{
			auto jukebox = makeEntity();
			auto audio = jukebox->addComponent<AudioComponent>();
			audio->LoadAudio("Enter_Press.wav");
			audio->PlayAudio();
			while (audio->AudioIsPlaying())
			{
				//do nothing
			}
			showResMenu();
			menuOpen = true;
		}
	} 
	
	
	// if the screen res menu is open
	else {
		
		// apply current selection and close menu
		if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Joystick::isButtonPressed(0, 7))) //start
		{
			// play audio
			auto jukebox = makeEntity();
			auto audio = jukebox->addComponent<AudioComponent>();
			audio->LoadAudio("Enter_Press.wav");
			audio->PlayAudio();
			while (audio->AudioIsPlaying())
			{
				//do nothing
			}
			menuOpen = false;
			closeResMenu();
		}
		
		// navigate down menu
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			updateResMenu(1, dt);
		}
		
		// navigate up menu
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			updateResMenu(-1, dt);
		}
		
		// joystick one way navigation
		if (Joystick::isButtonPressed(0, 3)) //triangle
		{
			updateResMenu(1, dt);
		}
	}
}

void OptionsScene::showResMenu() {
	
	// hide all menu states that were created in the load method
	for (auto &m : menuStates) {
		m->setVisible(false);
	}
	
	// show the open menu background and blanket highlighting	
	menuStates[3]->setVisible(true);
	menuStates[4]->setVisible(true);
	
	
	// get window size to check against preloaded resolution settings
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	// adjust position and spritesheet offset to show highlight for current res
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
	
	/*
	
	if one of the preloaded resolutions corresponds 
	with the current resolution highlight it
	
	*/
	
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
	
	// hide all menu states
	for (auto &m : menuStates) {
		m->setVisible(false);
	}
	
	// show current menu state
	menuState->setVisible(true);
	
	// resize window (event is handled in engine)
	if (menuState == menuStates[0]) {
		Renderer::getWindow().setSize(sf::Vector2u(800,600));
	} else if (menuState == menuStates[1]) {
		Renderer::getWindow().setSize(sf::Vector2u(1024,768));
	} else if (menuState == menuStates[2]) {
		Renderer::getWindow().setSize(sf::Vector2u(1366,768));
	}
	
	// display current resolution if applicable
	preSelectResolution();
	
}

void OptionsScene::updateResMenu(int direction, const double& dt) {
	
	// prevent single keypresses registering multiple events
	static double timer = 0.f;
	timer -= dt;
	
	if (timer < 0) {
		
		// get window size
		sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
		
		// get blanket highlighting entity position
		auto shape = menuStates[4]->getComponents<ShapeComponent>();
		sf::Vector2f pos = shape[0]->getShape().getPosition();
		
		// set default spritesheet offset
		sf::IntRect intRect = IntRect(0,0,168,34);
			
		// adjust the position and spritesheet offset of the highlight
		if (direction == 1) { // downwards
			
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
			
		} else { // upwards
			
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
		
		// set highlight position and spritesheet offset
		shape[0]->getShape().setPosition(pos);
		shape[0]->getShape().setTextureRect(intRect);
		
		timer = 0.12f;
		
	}		 
}

void OptionsScene::makeDescription(std::string t, sf::Vector2f p) {
	
	// create the text for a key description
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, "Rubik-Medium.ttf");
	text->setColor(sf::Color(200 , 190, 183));
	text->setCharacterSize(25);
	
	p.x -= text->getText().getLocalBounds().width;
	text->SetPosition(p);
	
}

void OptionsScene::makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p) {
		
	// create a key background
		
	auto entity = makeEntity();
	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(sf::Vector2f(40, 40));
	shape->getShape().setOrigin(20,20);
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, sf::IntRect(0,0,40,40));
	shape->getShape().setPosition(p);	
	
}

void OptionsScene::makeKeyText(std::string t, std::string f, sf::Color c, float s, sf::Vector2f p) {
	
	// create the text for a key
	
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(t, f);
	text->setOrigin(text->getText().getLocalBounds().width / 2, text->getText().getLocalBounds().height / 2);
	text->setColor(c);
	text->setCharacterSize(s);
	text->SetPosition(p);
	
}

void OptionsScene::resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p) {
	
	// create entities and set visibility for each menu state
	
	auto entity = makeEntity();
	entity->setVisible(v);

	auto shape = entity->addComponent<ShapeComponent>();
	shape->setShape<sf::RectangleShape>(s);
	shape->getShape().setOrigin(Vector2f(20,20));
	shape->getShape().setFillColor(sf::Color(255,255,255));
	shape->setTexture(sp, r);
	shape->getShape().setPosition(p);
	menuStates.push_back(entity);
	
	// if this one is visible then it is the current menu state
	if (v) {
		menuState = entity;
	}
	
	
}

void OptionsScene::load() {
	
	// create top section
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
	
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 305));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 355));
	makeKeys(keySprites, sf::Vector2f(windowSize.x / 2 + 20, 405));
	
	makeKeyText("S", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 300));
	makeKeyText("F", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 350));
	makeKeyText("R", "DroidSansMono.ttf", sf::Color(72,62,55), 25,sf::Vector2f(windowSize.x / 2 + 20, 400));
	
	
	
	// ============================== SCREEN CONTROLS ============================== // 
	
	// load graphics
	std::shared_ptr<sf::Texture> screenResSprites = Resources::get<sf::Texture>("ui_screen_res.png");
	std::shared_ptr<sf::Texture> fullScreenSprites = Resources::get<sf::Texture>("ui_fullscreen.png");
	
	// fullscreen indicator
	fullscreenIndicator = makeEntity();
	auto fsI = fullscreenIndicator->addComponent<ShapeComponent>();
	fsI->setShape<sf::RectangleShape>(sf::Vector2f(52, 40));
	fsI->getShape().setOrigin(Vector2f(20,20));
	fsI->getShape().setFillColor(sf::Color(255,255,255));
	fsI->setTexture(fullScreenSprites, sf::IntRect(0,0,52,40));
	fsI->getShape().setPosition(sf::Vector2f(windowSize.x / 2 + 80, 355));
	
	// invisible resolution indicators
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,0,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,33,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 33), screenResSprites, sf::IntRect(0,66,168,33), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 102), screenResSprites, sf::IntRect(0,99,168,102), sf::Vector2f(windowSize.x / 2 + 80, 308));
	resolutionIndicators(false, sf::Vector2f(168, 34), screenResSprites, sf::IntRect(0,201,168,34), sf::Vector2f(windowSize.x / 2 + 80, 308));
	
	// show the resolution indicator that corresponds with 
	// current screen size (if applicable)
	preSelectResolution();
	

	// ============================== FOOT ============================== // 
	
	// check if a game is in progress to customise message
	
	std::string backText;
	if (Engine::getLevel() == nullptr) {
		backText = "Press TAB to go back";
	} else {
		backText = "Press TAB to resume game";
	}
	auto back = makeEntity();
	auto goBack = back->addComponent<TextComponent>(backText, "WorstveldSling.ttf");
	goBack->setColor(sf::Color(200 , 190, 183));
	goBack->setCharacterSize(50);
	goBack->SetPosition({
		windowSize.x / 2 - goBack->getText().getLocalBounds().width / 2, 
		windowSize.y - 85
	});
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 100));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
}

void OptionsScene::unload() {
	
	// empty local menu states vector and variable as well
  _ents.list.clear();
  menuStates.clear();
  menuState = nullptr;
}
	
void OptionsScene::reload() {
	
}


