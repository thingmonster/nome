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
		std::vector<std::shared_ptr<Entity>> Scene::getEntities();
		
	protected:
		EntityManager _ents;
		
};



class LevelScene : public Scene {
		
	public:
		LevelScene() = default;
		virtual void update(const double& dt) = 0;
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void reload() = 0;
		virtual void render() = 0;
		virtual void restore(std::vector<std::shared_ptr<Entity>> entities) = 0;
		
		void destroy();

};



class Engine {
	
	private:
		static Scene* _activeScene;
		static LevelScene* _activeLevel;
		static void update();
		static void render();
		
		static bool readingInput;
		static void loadKeys();
		static void loadKeyStrings();
	
	public:
		Engine() = delete;
		~Engine() = delete;
		static void Start(int width, int height, const std::string& name, Scene* s);
		static void changeScene(Scene*);
		static void changeLevel(LevelScene*);
		static Scene* getLevel();
		static void restoreGame(std::vector<std::shared_ptr<Entity>> entities);
		static std::vector<std::shared_ptr<Entity>> getEntities();
		
		static vector<sf::Keyboard::Key> controls;
		static vector<sf::Keyboard::Key> keys;
		static vector<std::string> keyStrings;
		
		static std::string userInput;
		static void setReadingInput(bool b);
		static std::string getInput();
		
};
