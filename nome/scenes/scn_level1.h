#pragma once
#include "engine.h"


class Level1Scene : public Scene {
	
	private:
		static std::shared_ptr<sf::Texture> playerSprites;
		static std::shared_ptr<sf::Texture> enemySprites;
		std::shared_ptr<Entity> player;
		int maxEnemies = 1;
		bool loaded = false;
		
		
	public:
		Level1Scene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;
		void render() override;
		void spawn();
		void destroy();

};


