#pragma once
#include "engine.h"


class MenuScene : public Scene {
	
	private:
		sf::Text text;
		sf::Font font;
		
	public:
		MenuScene() = default;
		void update(const double& dt) override;
		void load() override;

};

