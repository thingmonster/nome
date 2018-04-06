#pragma once
#include "engine.h"


class RemapScene : public Scene {
	
	private:
	
	public:
		RemapScene() = default;
		void update(const double& dt) override;
		void load() override;
		void reload() override;
		
};

