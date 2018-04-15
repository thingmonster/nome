#pragma once

#include "engine.h"
#include "maths.h"
#include "decisions.h"
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"

using namespace sf;

/*

this file contains the definitions for each 
individual decision

*/


class StationaryDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("stationary");
		}
};

class SeekDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("seek");
		}
};

class FleeDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("flee");
		}
};


class WanderDecision : public DecisionTreeNode {
	
	public: 
		void makeDecision(Entity *owner) final {
			auto sm = owner->getComponents<StateMachineComponent>();
			sm[0]->changeState("wander");
		}
};

