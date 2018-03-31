
#include "engine.h"

using namespace std;
using namespace sf;

Scene* Engine::_activeScene = nullptr;



void Engine::update() {
	
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
		
	if (_activeScene != nullptr) {
    _activeScene->update(dt);
	}
	
}

void Engine::render() {
	_activeScene->render();
}

void Engine::changeScene(Scene* s) {
	_activeScene = s;
	_activeScene->load();
}

void Engine::Start(int width, int height, const std::string& name, Scene* s) {
	
	RenderWindow window(sf::VideoMode(width, height), name);
	window.setVerticalSyncEnabled(true);
	
	changeScene(s);
	
	while (window.isOpen()) {
		
		Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
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












void Scene::render() {
	cout << "scene-render ";
}

void Scene::update(const double& dt) { 
	cout << "scene-update ";
}

Scene::~Scene() {}


