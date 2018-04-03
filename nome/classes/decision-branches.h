#pragma once

#include "decisions.h"



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
			// cout << "dist "<< dist << " | " << "_distance "<< _distance << endl;
			if (dist < _distance) {
				// cout << "true" << endl;
				return _trueNode;
			} else {
				// cout << "false" << endl;
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
			// cout << "dd ";
		}
		
};
