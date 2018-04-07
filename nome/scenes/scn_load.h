#pragma once
#include "engine.h"
#include <fstream>



class LoadScene : public Scene {
	
	private:
		void loadGame();
		std::shared_ptr<Entity> loadEntity(std::string s);
		std::vector<LevelScene*> levels;
		
		
	public:
		LoadScene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;

};

