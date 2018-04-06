#pragma once
#include "engine.h"
#include <fstream>



class SaveScene : public Scene {
	
	private:
		void saveGame();
		static std::shared_ptr<sf::Texture> inputField;
		std::string userInput;
		std::shared_ptr<Entity> userText;
		std::shared_ptr<Entity> cursor;
		sf::Vector2f windowSize;
		
		
	public:
		SaveScene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;

};

