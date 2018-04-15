#pragma once

#include "ecm.h"
#include "../classes/decision-branches.h"
#include "../classes/decision-leaves.h"
#include <iostream>



class DecisionTreeComponent : public Component {
	
	public:
		std::shared_ptr<DecisionTreeNode> _decisionTree;
		
	public:
		void update(double) override;
		void render() override {}
		explicit DecisionTreeComponent(Entity *p, std::shared_ptr<DecisionTreeNode> decisionTree);
		DecisionTreeComponent() = delete;
		
		void setDecisionTree(std::shared_ptr<DecisionTreeNode> tree);
		
};






