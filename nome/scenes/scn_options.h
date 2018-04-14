#pragma once
#include "scn_ui.h"


class OptionsScene : public UIScene {
	
	private:
		std::shared_ptr<Entity> fullscreenIndicator;
	
	public:
		OptionsScene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;
		
		std::vector<std::shared_ptr<Entity>> menuStates;
		std::shared_ptr<Entity> menuState;

		bool menuOpen;
		void showResMenu();
		void closeResMenu();
		void preSelectResolution();
		void updateResMenu(int direction, const double& dt);
		void makeDescription(std::string t, sf::Vector2f p);
		void makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p);
		void makeKeyText(std::string t, std::string f, sf::Color c, float s, sf::Vector2f p);
		void resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p);
};

