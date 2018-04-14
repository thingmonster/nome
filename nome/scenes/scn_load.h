#pragma once
#include "scn_ui.h"
#include <fstream>



class LoadScene : public UIScene {
	
	private:
		void loadGame();
		std::shared_ptr<Entity> highlight;
		int highlightPosition = 0;
		std::vector<std::string> filenames;
		std::vector<std::shared_ptr<Entity>> fileEntities;
		std::shared_ptr<Entity> loadEntity(std::string s);
		std::vector<LevelScene*> levels;
		
		
	public:
		LoadScene() = default;
		void update(const double& dt) override;
		void load();
		void unload() override;
		void reload() override;
		// void render();

};

