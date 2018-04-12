#pragma once

#include "engine.h"
#include "levelsystem.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../components/cmp_movement.h"
#include "../components/cmp_player_movement.h"
#include "../components/cmp_steering.h"
#include "../components/cmp_pathfinding.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_audio.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <random>
#include <chrono>



class Level1Scene : public LevelScene {
	
	private:
		static std::shared_ptr<sf::Texture> playerSprites;
		static std::shared_ptr<sf::Texture> enemySprites;
		std::shared_ptr<Entity> player;
		std::shared_ptr<Entity> ball;
		int maxEnemies = 3;
		bool loaded = false;
		
		
	public:
		Level1Scene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;
		void render();
		void spawn();
		void resize();
		void restore(std::vector<std::shared_ptr<Entity>> entities) override;
		void makePlayer(std::shared_ptr<Entity> player);
		void makeBall(std::shared_ptr<Entity> ball);
		void makeEnemy(std::shared_ptr<Entity> enemy);
		void addEnemyAI(std::shared_ptr<Entity> enemy);
		void updateEnemyAI(std::shared_ptr<Entity> enemy);
		std::shared_ptr<DistanceDecision> decisionTree();

};


