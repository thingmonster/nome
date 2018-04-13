#pragma once
#include "scn_ui.h"
#include "engine.h"
#include <iomanip>
#include <sstream>
#include <string>



class DeathScene : public UIScene {
	
	public:
		DeathScene() = default;
		void update(const double& dt) override;
		void load();
		void unload() override;
		void reload() override;

};

