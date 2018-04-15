#pragma once
#include "scn_ui.h"
#include <algorithm>


class PausedScene : public UIScene {
	
	private:
	
	public:
		PausedScene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;
		
		void makeDescription(std::string t, sf::Vector2f p);
		void makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p);
		void makeKeyText(std::string t, sf::Vector2f p);

};

