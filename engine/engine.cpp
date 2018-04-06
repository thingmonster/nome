
#include "engine.h"

using namespace std;
using namespace sf;

Scene* Engine::_activeScene = nullptr;



// ======================== ENGINE ======================== //
	
vector<sf::Keyboard::Key> Engine::controls;	
	
void Engine::changeScene(Scene* s) {
	_activeScene = s;
	_activeScene->load();
}

void Engine::Start(int width, int height, const std::string& name, Scene* s) {
	
	Engine::controls.push_back(Keyboard::Left);
	Engine::controls.push_back(Keyboard::Right);
	Engine::controls.push_back(Keyboard::Up);
	Engine::controls.push_back(Keyboard::Down);
	
	
	RenderWindow window(sf::VideoMode(width, height), name);
	window.setVerticalSyncEnabled(true);
	
	Renderer::initialise(window);
	changeScene(s);
	
	
	while (window.isOpen()) {
		
		Event event;
    while (window.pollEvent(event)) {
			
			if (controls.size() < 4) {
					
				if (event.type == sf::Event::EventType::KeyPressed){
						cout << event.key.code << endl;
				}
			}	
			
      if (event.type == Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::Resized) {
				std::cout << "resize: ("  << event.size.width << ',' << event.size.height << ") -> " << std::endl;
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				changeScene(_activeScene);
			}
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
		}
		
			
		window.clear();
		update();
		render();
		window.display();
	}
}

void Engine::update() {
	
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
		
	if (_activeScene != nullptr) {
    _activeScene->update(dt);
	}
	
}

void Engine::render() {
	_activeScene->render();
	Renderer::render();
}

// std::shared_ptr<sf::Keyboard::Key[4]> getControls() {
	// return controls;
// }
// std::shared_ptr<sf::Keyboard::Key[4]> getC() {
	// return _c;
// }








// ======================== SCENE ======================== //
	


void Scene::render() {
	_ents.render();
}

void Scene::update(const double& dt) { 
	_ents.update(dt); 
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	_ents.list.push_back(e);
	return std::move(e);
}

Scene::~Scene() {}


