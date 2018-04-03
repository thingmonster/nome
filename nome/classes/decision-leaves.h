#pragma once

#include "engine.h"
#include "maths.h"
#include "decisions.h"
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"

using namespace sf;


class StationaryDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			// cout << "stationary" << endl;
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("stationary");
		}
};

class SeekDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			// cout << "seek" << endl;
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("seek");
		}
};

class FleeDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			// cout << "flee" << endl;
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("flee");
		}
};

