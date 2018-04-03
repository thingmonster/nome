#include "cmp_decision_tree.h"

using namespace std;




DecisionTreeComponent::DecisionTreeComponent(Entity *p, shared_ptr<DecisionTreeNode> decisionTree)
	: _decisionTree(decisionTree), Component(p) {}
	
void DecisionTreeComponent::update(double dt) {
	_decisionTree->makeDecision(_parent);
}
