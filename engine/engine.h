#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "physics.h"

class Scene {
	
	public:
		Scene() = default;
		virtual ~Scene();
		virtual void update(const double& dt);
		virtual void render();
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void reload() = 0;
		virtual void resize() = 0;
		std::shared_ptr<Entity> Scene::makeEntity();
		std::shared_ptr<Entity> Scene::makeEntity(std::string tag);
		std::vector<std::shared_ptr<Entity>> Scene::getEntities();
		Vector2f windowSize;
		
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
		
		void resize();
		void destroy();
		
		int deathCount = 0;
		void setDeathCount();
		int getDeathCount();

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
	
		static void resize();
		
		static RenderWindow window;
		static std::string windowMode;
		static bool changingMode;
		
	public:
		Engine() = delete;
		~Engine() = delete;
		static void Start(int width, int height, const std::string& name, Scene* s);
		static void changeScene(Scene*);
		static void changeLevel(LevelScene*);
		static LevelScene* getLevel();
		
		static void restoreGame(std::vector<std::shared_ptr<Entity>> entities);
		static std::vector<std::shared_ptr<Entity>> getEntities();
		
		static vector<sf::Keyboard::Key> controls;
		static vector<sf::Joystick::Axis> joycon;
		static vector<sf::Keyboard::Key> keys;
		static vector<std::string> keyStrings;
		
		static std::string userInput;
		static void setReadingInput(bool b);
		static std::string getInput();
		
		static float getLifespan();
		
		static void changeMode();
		
		
};
