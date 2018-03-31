#pragma once
#include "engine.h"


class MenuScene : public Scene {
	
	public:
		MenuScene() = default;
		void update(const double& dt) override;
		void load() override;

};

