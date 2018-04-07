#pragma once
#include "scn_ui.h"


class RemapScene : public UIScene {
	
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

