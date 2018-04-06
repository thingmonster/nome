#pragma once
#include "engine.h"


class MenuScene : public Scene {
	
	public:
		MenuScene() = default;
		void update(const double& dt) override;
		void load() override;
		void reload() override;
		void buildKeys();
		void textureKey(int c, sf::Vector2f kPos, sf::Vector2f dPos);
		void textKey(int c, sf::Vector2f kPos, sf::Vector2f dPos, int direction);
		int controlCount();

};

