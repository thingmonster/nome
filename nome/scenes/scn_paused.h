#pragma once
#include "engine.h"


class PausedScene : public Scene {
	
	private:
	
	public:
		PausedScene() = default;
		void update(const double& dt) override;
		void load() override;
		void reload() override;
		
		void makeDescription(std::string t, sf::Vector2f p);
		void makeKeys(std::shared_ptr<sf::Texture> sp, sf::Vector2f p);
		void makeKeyText(std::string t, sf::Vector2f p);
		void resolutionIndicators(bool v, sf::Vector2f s, std::shared_ptr<sf::Texture> sp, sf::IntRect r, sf::Vector2f p);
};

