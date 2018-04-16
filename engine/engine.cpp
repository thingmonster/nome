
#include "engine.h"

using namespace std;
using namespace sf;




	
// ======================== ENGINE ======================== //

/* window modes */

RenderWindow Engine::window;
std::string Engine::windowMode = "default";
bool Engine::changingMode = false;

void Engine::changeMode()  {
	changingMode = true;
}

std::string Engine::getMode()  {
	return windowMode;
}

/* end window modes */


/* reading input for remapping and saving games */

bool Engine::readingInput = false;
std::string Engine::userInput;	

vector<sf::Keyboard::Key> Engine::controls;
vector<sf::Joystick::Axis> Engine::joycon;
vector<sf::Keyboard::Key> Engine::keys;	
vector<std::string> Engine::keyStrings;

void Engine::loadKeys() {
	Engine::keys.push_back(Keyboard::A);
	Engine::keys.push_back(Keyboard::B);
	Engine::keys.push_back(Keyboard::C);
	Engine::keys.push_back(Keyboard::D);
	Engine::keys.push_back(Keyboard::E);
	Engine::keys.push_back(Keyboard::F);
	Engine::keys.push_back(Keyboard::G);
	Engine::keys.push_back(Keyboard::H);
	Engine::keys.push_back(Keyboard::I);
	Engine::keys.push_back(Keyboard::J);
	Engine::keys.push_back(Keyboard::K);
	Engine::keys.push_back(Keyboard::L);
	Engine::keys.push_back(Keyboard::M);
	Engine::keys.push_back(Keyboard::N);
	Engine::keys.push_back(Keyboard::O);
	Engine::keys.push_back(Keyboard::P);
	Engine::keys.push_back(Keyboard::Q);
	Engine::keys.push_back(Keyboard::R);
	Engine::keys.push_back(Keyboard::S);
	Engine::keys.push_back(Keyboard::T);
	Engine::keys.push_back(Keyboard::U);
	Engine::keys.push_back(Keyboard::V);
	Engine::keys.push_back(Keyboard::W);
	Engine::keys.push_back(Keyboard::X);
	Engine::keys.push_back(Keyboard::Y);
	Engine::keys.push_back(Keyboard::Z);
	Engine::keys.push_back(Keyboard::Num0);
	Engine::keys.push_back(Keyboard::Num1);
	Engine::keys.push_back(Keyboard::Num2);
	Engine::keys.push_back(Keyboard::Num3);
	Engine::keys.push_back(Keyboard::Num4);
	Engine::keys.push_back(Keyboard::Num5);
	Engine::keys.push_back(Keyboard::Num6);
	Engine::keys.push_back(Keyboard::Num7);
	Engine::keys.push_back(Keyboard::Num8);
	Engine::keys.push_back(Keyboard::Num9);
	Engine::keys.push_back(Keyboard::Escape);
	Engine::keys.push_back(Keyboard::LControl);
	Engine::keys.push_back(Keyboard::LShift);
	Engine::keys.push_back(Keyboard::LAlt);
	Engine::keys.push_back(Keyboard::LSystem);
	Engine::keys.push_back(Keyboard::RControl);
	Engine::keys.push_back(Keyboard::RShift);
	Engine::keys.push_back(Keyboard::RAlt);
	Engine::keys.push_back(Keyboard::RSystem);
	Engine::keys.push_back(Keyboard::Menu);
	Engine::keys.push_back(Keyboard::LBracket);
	Engine::keys.push_back(Keyboard::RBracket);
	Engine::keys.push_back(Keyboard::SemiColon);
	Engine::keys.push_back(Keyboard::Comma);
	Engine::keys.push_back(Keyboard::Period);
	Engine::keys.push_back(Keyboard::Quote);
	Engine::keys.push_back(Keyboard::Slash);
	Engine::keys.push_back(Keyboard::BackSlash);
	Engine::keys.push_back(Keyboard::Tilde);
	Engine::keys.push_back(Keyboard::Equal);
	Engine::keys.push_back(Keyboard::Dash);
	Engine::keys.push_back(Keyboard::Space);
	Engine::keys.push_back(Keyboard::Return);
	Engine::keys.push_back(Keyboard::BackSpace);
	Engine::keys.push_back(Keyboard::Tab);
	Engine::keys.push_back(Keyboard::PageUp);
	Engine::keys.push_back(Keyboard::PageDown);
	Engine::keys.push_back(Keyboard::End);
	Engine::keys.push_back(Keyboard::Home);
	Engine::keys.push_back(Keyboard::Insert);
	Engine::keys.push_back(Keyboard::Delete);
	Engine::keys.push_back(Keyboard::Add);
	Engine::keys.push_back(Keyboard::Subtract);
	Engine::keys.push_back(Keyboard::Multiply);
	Engine::keys.push_back(Keyboard::Divide);
	Engine::keys.push_back(Keyboard::Left);
	Engine::keys.push_back(Keyboard::Right);
	Engine::keys.push_back(Keyboard::Up);
	Engine::keys.push_back(Keyboard::Down);
	Engine::keys.push_back(Keyboard::Numpad0);
	Engine::keys.push_back(Keyboard::Numpad1);
	Engine::keys.push_back(Keyboard::Numpad2);
	Engine::keys.push_back(Keyboard::Numpad3);
	Engine::keys.push_back(Keyboard::Numpad4);
	Engine::keys.push_back(Keyboard::Numpad5);
	Engine::keys.push_back(Keyboard::Numpad6);
	Engine::keys.push_back(Keyboard::Numpad7);
	Engine::keys.push_back(Keyboard::Numpad8);
	Engine::keys.push_back(Keyboard::Numpad9);
	Engine::keys.push_back(Keyboard::F1);
	Engine::keys.push_back(Keyboard::F2);
	Engine::keys.push_back(Keyboard::F3);
	Engine::keys.push_back(Keyboard::F4);
	Engine::keys.push_back(Keyboard::F5);
	Engine::keys.push_back(Keyboard::F6);
	Engine::keys.push_back(Keyboard::F7);
	Engine::keys.push_back(Keyboard::F8);
	Engine::keys.push_back(Keyboard::F9);
	Engine::keys.push_back(Keyboard::F10);
	Engine::keys.push_back(Keyboard::F11);
	Engine::keys.push_back(Keyboard::F12);
	Engine::keys.push_back(Keyboard::F13);
	Engine::keys.push_back(Keyboard::F14);
	Engine::keys.push_back(Keyboard::F15);
	Engine::keys.push_back(Keyboard::Pause);
	Engine::keys.push_back(Keyboard::KeyCount);
	
}

void Engine::loadKeyStrings() {
	Engine::keyStrings.push_back("A");
	Engine::keyStrings.push_back("B");
	Engine::keyStrings.push_back("C");
	Engine::keyStrings.push_back("D");
	Engine::keyStrings.push_back("E");
	Engine::keyStrings.push_back("F");
	Engine::keyStrings.push_back("G");
	Engine::keyStrings.push_back("H");
	Engine::keyStrings.push_back("I");
	Engine::keyStrings.push_back("J");
	Engine::keyStrings.push_back("K");
	Engine::keyStrings.push_back("L");
	Engine::keyStrings.push_back("M");
	Engine::keyStrings.push_back("N");
	Engine::keyStrings.push_back("O");
	Engine::keyStrings.push_back("P");
	Engine::keyStrings.push_back("Q");
	Engine::keyStrings.push_back("R");
	Engine::keyStrings.push_back("S");
	Engine::keyStrings.push_back("T");
	Engine::keyStrings.push_back("U");
	Engine::keyStrings.push_back("V");
	Engine::keyStrings.push_back("W");
	Engine::keyStrings.push_back("X");
	Engine::keyStrings.push_back("Y");
	Engine::keyStrings.push_back("Z");
	Engine::keyStrings.push_back("0");
	Engine::keyStrings.push_back("1");
	Engine::keyStrings.push_back("2");
	Engine::keyStrings.push_back("3");
	Engine::keyStrings.push_back("4");
	Engine::keyStrings.push_back("5");
	Engine::keyStrings.push_back("6");
	Engine::keyStrings.push_back("7");
	Engine::keyStrings.push_back("8");
	Engine::keyStrings.push_back("9");
	Engine::keyStrings.push_back("Escape");
	Engine::keyStrings.push_back("LControl");
	Engine::keyStrings.push_back("LShift");
	Engine::keyStrings.push_back("LAlt");
	Engine::keyStrings.push_back("LSystem");
	Engine::keyStrings.push_back("RControl");
	Engine::keyStrings.push_back("RShift");
	Engine::keyStrings.push_back("RAlt");
	Engine::keyStrings.push_back("RSystem");
	Engine::keyStrings.push_back("Menu");
	Engine::keyStrings.push_back("LBracket");
	Engine::keyStrings.push_back("RBracket");
	Engine::keyStrings.push_back("SemiColon");
	Engine::keyStrings.push_back("Comma");
	Engine::keyStrings.push_back("Period");
	Engine::keyStrings.push_back("Quote");
	Engine::keyStrings.push_back("Slash");
	Engine::keyStrings.push_back("BackSlash");
	Engine::keyStrings.push_back("Tilde");
	Engine::keyStrings.push_back("Equal");
	Engine::keyStrings.push_back("Dash");
	Engine::keyStrings.push_back("Space");
	Engine::keyStrings.push_back("Return");
	Engine::keyStrings.push_back("BackSpace");
	Engine::keyStrings.push_back("Tab");
	Engine::keyStrings.push_back("PageUp");
	Engine::keyStrings.push_back("PageDown");
	Engine::keyStrings.push_back("End");
	Engine::keyStrings.push_back("Home");
	Engine::keyStrings.push_back("Insert");
	Engine::keyStrings.push_back("Delete");
	Engine::keyStrings.push_back("Add");
	Engine::keyStrings.push_back("Subtract");
	Engine::keyStrings.push_back("Multiply");
	Engine::keyStrings.push_back("Divide");
	Engine::keyStrings.push_back("Left");
	Engine::keyStrings.push_back("Right");
	Engine::keyStrings.push_back("Up");
	Engine::keyStrings.push_back("Down");
	Engine::keyStrings.push_back("Number pad 0");
	Engine::keyStrings.push_back("Number pad 1");
	Engine::keyStrings.push_back("Number pad 2");
	Engine::keyStrings.push_back("Number pad 3");
	Engine::keyStrings.push_back("Number pad 4");
	Engine::keyStrings.push_back("Number pad 5");
	Engine::keyStrings.push_back("Number pad 6");
	Engine::keyStrings.push_back("Number pad 7");
	Engine::keyStrings.push_back("Number pad 8");
	Engine::keyStrings.push_back("Number pad 9");
	Engine::keyStrings.push_back("F1");
	Engine::keyStrings.push_back("F2");
	Engine::keyStrings.push_back("F3");
	Engine::keyStrings.push_back("F4");
	Engine::keyStrings.push_back("F5");
	Engine::keyStrings.push_back("F6");
	Engine::keyStrings.push_back("F7");
	Engine::keyStrings.push_back("F8");
	Engine::keyStrings.push_back("F9");
	Engine::keyStrings.push_back("F10");
	Engine::keyStrings.push_back("F11");
	Engine::keyStrings.push_back("F12");
	Engine::keyStrings.push_back("F13");
	Engine::keyStrings.push_back("F14");
	Engine::keyStrings.push_back("F15");
	Engine::keyStrings.push_back("Pause");
	Engine::keyStrings.push_back("KeyCount");
	
}
	
void Engine::setReadingInput(bool b) {
	readingInput = b;
}

std::string Engine::getInput() {
	std::string ret = userInput;
	userInput = "";
	return ret;
}

/* end reading input */



/* managing scenes */

Scene* Engine::_activeScene = nullptr;
LevelScene* Engine::_activeLevel = nullptr;

void Engine::changeScene(Scene* s) {
	if (_activeScene != nullptr) {
		_activeScene->unload();
	}
	_activeScene = s;
	_activeScene->load();
}

void Engine::changeLevel(LevelScene* s) {
	if (_activeLevel != nullptr) {
		_activeLevel->destroy();
	}
	_activeLevel = s;
}

LevelScene* Engine::getLevel() {
	return _activeLevel;
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities() {
	return Engine::getLevel()->_ents.list;
}

void Engine::restoreGame(std::vector<std::shared_ptr<Entity>> entities) {
	_activeScene = _activeLevel;
	_activeLevel->restore(entities);
}

void Engine::resize() {
	_activeScene->resize();
}

void Engine::endGame() {
	if (_activeLevel != nullptr) {
		_activeLevel->destroy();
	}
	_activeLevel = nullptr;
}

/* end managing scenes */




/* lifespan clock */

static sf::Clock lifeSpan;	
	
float Engine::getLifespan() {	
	float lifespan = lifeSpan.restart().asSeconds();
	return lifespan;
}
	
/* end lifespan clock */

	
	
/* main methods */
	
void Engine::Start(int width, int height, const std::string& name, Scene* s) {
	
	// set up default controls
	Engine::controls.push_back(Keyboard::Left);
	Engine::controls.push_back(Keyboard::Right);
	Engine::controls.push_back(Keyboard::Up);
	Engine::controls.push_back(Keyboard::Down);
	Engine::joycon.push_back(Joystick::X);
	Engine::joycon.push_back(Joystick::Y);
	
	// set up sfml key references
	loadKeys();
	loadKeyStrings();
	
	// set up window and vsync
	window.create(sf::VideoMode(width, height), name, sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	
	// initialise renderer and physics
	Renderer::initialise(window);
	Physics::initialise();
	
	// set active scene
	changeScene(s);			
	
	while (window.isOpen()) {
		
		
		// check for user input and window events
		Event event;
    while (window.pollEvent(event)) {
			
			// if window mode is being toggled close and reopen
			if (changingMode) {
				window.close();
				if (windowMode == "default") {
					window.create(sf::VideoMode(width, height), name, sf::Style::Fullscreen);
					windowMode = "fullscreen";
				} else {
					window.create(sf::VideoMode(width, height), name, sf::Style::Default);
					windowMode = "default";
				}
				window.setVerticalSyncEnabled(true);
				changingMode = false;
			} // end toggling window mode
			
			
			
			// if controls are being remapped read user input
			if (controls.size() < 4) {
					
				if (event.type == sf::Event::EventType::KeyPressed){
						controls.push_back(keys[event.key.code]);
				}
			}// end remapping controls

			
			
			// if reading input for saved game filename
			if (readingInput) {
					
				if (
					(event.type == sf::Event::EventType::KeyPressed) &&
					(event.key.code < 37)
				) {
					userInput += keyStrings[event.key.code];
				}
			} // end reading filename input
			
			
			
			// close window if necessary
      if (event.type == Event::Closed) {
        window.close();
      } 
			
			// resize window if necessary, reload current scene and pass the command to it
			else if (event.type == sf::Event::Resized) {
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				changeScene(_activeScene);
				resize();
			} // end resize window
			
    } // end pollEvent
		
		
		
		// close window if escape pressed
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
		}
		
		
		
		// main functions				
		window.clear();
		update();
		render();
		window.display();
	}
	
	
	
	// game has ended
  window.close();
	Physics::shutdown();
	
}

void Engine::update() {
	
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	
	// step physics world and update current scene
	if (_activeScene != nullptr) {
    if (_activeScene == _activeLevel) {
			Physics::update(dt);
		}
    _activeScene->update(dt);
	}
	
}

void Engine::render() {
	_activeScene->render();
	Renderer::render();
}







// ======================== SCENE ======================== //
	

/* main methods */

void Scene::render() {
	_ents.render();
}

void Scene::update(const double& dt) { 
	_ents.update(dt); 
}

Scene::~Scene() {}


/* make an entity with a tag */

std::shared_ptr<Entity> Scene::makeEntity(std::string tag) {
	auto e = make_shared<Entity>(this, tag);
	_ents.list.push_back(e);
	return std::move(e);
}


/* make an entity without a tag */

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	_ents.list.push_back(e);
	return std::move(e);
}





// ======================== LEVELSCENE ======================== //
	

/* destroy all current level's entities and unload */
	
void LevelScene::destroy() {
	_ents.list.clear();
	loaded = false;
}


/* resize and restyle current map and entities */

void LevelScene::resize() {
}


/* beetle death count */

void LevelScene::setDeathCount() {
	deathCount++;
}

int LevelScene::getDeathCount() {
	return deathCount;
}


