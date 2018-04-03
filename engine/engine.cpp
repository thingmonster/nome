
#include "engine.h"

using namespace std;
using namespace sf;

Scene* Engine::_activeScene = nullptr;


// ======================== ENGINE ======================== //
	

void Engine::changeScene(Scene* s) {
	_activeScene = s;
	_activeScene->load();
}

void Engine::Start(int width, int height, const std::string& name, Scene* s) {
	
	RenderWindow window(sf::VideoMode(width, height), name);
	window.setVerticalSyncEnabled(true);
	
	Renderer::initialise(window);
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


