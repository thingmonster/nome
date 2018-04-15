#pragma once

#include "decisions.h"

/*

this file contains the definitions for RandomDecision,
RandomMultiDecision and DistanceDecision

*/



class RandomDecision : public Decision {
	
	protected:
		std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) final;
		
	public:
		RandomDecision(std::shared_ptr<DecisionTreeNode> trueNode, std::shared_ptr<DecisionTreeNode> falseNode)
			: Decision(trueNode, falseNode) {}
			
};



class RandomMultiDecision : public MultiDecision {
	
	protected:
		std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) override final;
		
	public:
		RandomMultiDecision(const std::vector<std::shared_ptr<DecisionTreeNode>> &childNodes) 
		: MultiDecision(childNodes) {}
			
};




class DistanceDecision : public Decision {
	
	private:
		std::shared_ptr<Entity> _player;
		float _distance;
		
	protected:
		std::shared_ptr<DecisionTreeNode> getBranch(Entity *owner) final {
			float dist = sf::length(owner->getPosition() - _player->getPosition());
			if (dist < _distance) {
				return _trueNode;
			} else {
				return _falseNode;
			}
		}		
	
	public:
		DistanceDecision(
			std::shared_ptr<Entity> player, 
			float distance, 
			std::shared_ptr<DecisionTreeNode> trueNode,
			std::shared_ptr<DecisionTreeNode> falseNode
		) : _player(player), _distance(distance), Decision(trueNode, falseNode) {
		}
		
};
