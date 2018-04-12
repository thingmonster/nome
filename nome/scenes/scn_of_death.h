#pragma once
#include "scn_ui.h"



class DeathScene : public UIScene {
	
	public:
		DeathScene() = default;
		void update(const double& dt) override;
		void load();
		void unload() override;
		void reload() override;

};

