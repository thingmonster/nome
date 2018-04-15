#pragma once

#include "ecm.h"
#include "maths.h"
#include <memory>
#include <vector>
#include <random>
#include <chrono>

/*

this file contains the definitions for DecisionTreeNode,
Decision and MultiDecision

*/

class DecisionTreeNode {
	
	public:
		virtual ~DecisionTreeNode() = default;
		virtual void makeDecision(Entity *owner) = 0;
};


class Decision : public DecisionTreeNode {
	
	protected:
		std::shared_ptr<DecisionTreeNode> _trueNode;
		std::shared_ptr<DecisionTreeNode> _falseNode;
		virtual std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) = 0;
		
	public:
		Decision(std::shared_ptr<DecisionTreeNode> trueNode, std::shared_ptr<DecisionTreeNode> falseNode)
			: _trueNode(trueNode), _falseNode(falseNode) {}
		void makeDecision(Entity* owner) {
			getBranch(owner)->makeDecision(owner);
		}
};

class MultiDecision : public DecisionTreeNode {
	
	protected:
		std::vector<std::shared_ptr<DecisionTreeNode>> _childNodes;
		virtual std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) = 0;
		
	public:
		MultiDecision(const std::vector<std::shared_ptr<DecisionTreeNode>> &childNodes)
			: MultiDecision(childNodes) {}
		void makeDecision(Entity* owner) {
			getBranch(owner)->makeDecision(owner);
		}
};


