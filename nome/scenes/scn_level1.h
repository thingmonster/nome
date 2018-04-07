#pragma once

#include "../game.h"
#include "engine.h"
#include "levelsystem.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../components/cmp_movement.h"
#include "../components/cmp_player_movement.h"
#include "../components/cmp_steering.h"
#include "../components/cmp_pathfinding.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_decision_tree.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <random>
#include <chrono>



class Level1Scene : public LevelScene {
	
	private:
		static std::shared_ptr<sf::Texture> playerSprites;
		static std::shared_ptr<sf::Texture> enemySprites;
		std::shared_ptr<Entity> player;
		int maxEnemies = 1;
		bool loaded = false;
		
		
	public:
		Level1Scene() = default;
		void update(const double& dt);
		void load() ;
		void unload() ;
		void reload() ;
		void render() ;
		void spawn();
		void destroy();

};


