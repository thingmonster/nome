#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include <memory>

class Scene {
	
	public:
		Scene() = default;
		virtual ~Scene();
		virtual void update(const double& dt);
		void render();
		virtual void load() = 0;
		
};



class Engine {
	
	private:
		static Scene* _activeScene;
		static void update();
		static void render();
	
	public:
		Engine() = delete;
		~Engine() = delete;
		static void Start(int width, int height, const std::string& name, Scene* s);
		static void changeScene(Scene*);
		
};
