#include "cmp_decision_tree.h"

using namespace std;




DecisionTreeComponent::DecisionTreeComponent(Entity *p, shared_ptr<DecisionTreeNode> decisionTree)
	: _decisionTree(decisionTree), Component(p) {}
	
void DecisionTreeComponent::update(double dt) {
	_decisionTree->makeDecision(_parent);
}

void DecisionTreeComponent::setDecisionTree(std::shared_ptr<DecisionTreeNode> tree) {
	DecisionTreeComponent::_decisionTree = tree;
}

// void DecisionTreeComponent::setDecisionTree() {
	// cout << "dt" << endl;
	// DecisionTreeComponent::_decisionTree = tree;
// }