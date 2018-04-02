#pragma once
#include "engine.h"


class Level1Scene : public Scene {
	
	public:
		Level1Scene() = default;
		void update(const double& dt) override;
		void load() override;
		void render() override;
		static std::shared_ptr<sf::Texture> spritesheet;

};

