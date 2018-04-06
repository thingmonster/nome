#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <ecm.h>
#include "system_renderer.h"

class Scene {
	
	public:
		Scene() = default;
		virtual ~Scene();
		virtual void update(const double& dt);
		virtual void render();
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void reload() = 0;
		std::shared_ptr<Entity> Scene::makeEntity();
		
	protected:
		EntityManager _ents;
		
};



class Engine {
	
	private:
		static Scene* _activeScene;
		static Scene* _activeLevel;
		static void update();
		static void render();
		static bool isRemapping;
		static void loadKeys();
		static void loadKeyStrings();
	
	public:
		Engine() = delete;
		~Engine() = delete;
		static void Start(int width, int height, const std::string& name, Scene* s);
		static void changeScene(Scene*);
		static void changeLevel(Scene*);
		static vector<sf::Keyboard::Key> controls;
		static vector<sf::Keyboard::Key> keys;
		static vector<std::string> keyStrings;
		
};
