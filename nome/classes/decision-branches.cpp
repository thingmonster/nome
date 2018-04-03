
#include "decision-branches.h"


 
std::shared_ptr<DecisionTreeNode> RandomDecision::getBranch(Entity *owner) {
	
	static random_device rd;
	static default_random_engine e(rd());
	static uniform_int_distribution<int> dist(0,1);
	bool choice = dist(e) == 0;
	
	if (choice) {
		return _trueNode;
	} else {
		return _falseNode;
	}
}

std::shared_ptr<DecisionTreeNode> RandomMultiDecision::getBranch(Entity *owner) {
	
	static random_device rd;
	static default_random_engine e(rd());
	static uniform_int_distribution<size_t> dist(0,_childNodes.size());
	return _childNodes[dist(e)];
}

