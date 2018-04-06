#pragma once
#include "engine.h"
#include <algorithm>


class RemapScene : public Scene {
	
	private:
		void queryKey();
		bool remapping;
		int controlCount;
		bool finished;
		void finish();
		std::shared_ptr<Entity> instructions;
	
	public:
		RemapScene() = default;
		void update(const double& dt) override;
		void load() override;
		void unload() override;
		void reload() override;
		
};

