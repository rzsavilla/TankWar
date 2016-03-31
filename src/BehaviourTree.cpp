/*!
	Define all Behaviour tree class functions
	-CompositeNode
	-Selector
	-Sequence
	-Root
*/

#include "BehaviourTree.h"

//Default Contructor
BehaviourTree::BehaviourTree() {

}

void BehaviourTree::setRootChild(Node* rootChild) const{
	root->setChild(rootChild);
}

bool BehaviourTree::run() const{
	return root->run();
}

////////////COMPOSITE NODE/////////////////////

const std::vector<BehaviourTree::Node*>& BehaviourTree::CompositeNode::getChildren() const{
	return children;
}

void BehaviourTree::CompositeNode::addChild(Node* child) {
	children.emplace_back(child);
}

void BehaviourTree::CompositeNode::addChildren(std::initializer_list<Node*>&& newChildren) {
	for (Node* child : newChildren) { //Iterate through list of nodes
		addChild(child);	//Add child is list
	}
}

template <typename CONTAINER>
void BehaviourTree::CompositeNode::addChildren(const CONTAINER& newChildren) {
	for (Node* child : newChildren) {
		addChild(child);
	}
}

std::vector<BehaviourTree::Node*> BehaviourTree::CompositeNode::childrenShuffled() const {
	std::vector<Node*> temp = children;  std::random_shuffle(temp.begin(), temp.end());  
	return temp; 
}

////////SELECTOR/////////
//Selectector node succeeds if a single child node is sucessful
bool BehaviourTree::Selector::run() {
	for (Node* child : getChildren()) {			//Iterate through child nodes
		if (child->run()) {
			return true;
		}
	}
	return false;
}

////////SEQUENCE/////////
//Runs all child nodes if a single node fails then this whole node fails
bool BehaviourTree::Sequence::run() {
	for (Node* child : getChildren()) {			
		if (!child->run()) {
			return false;
		}
	}
	return true;
}

////////ROOT/////////
void BehaviourTree::Root::setChild(Node* newChild) {
	this->setChild(newChild);
}

bool BehaviourTree::Root::run() {
	return child->run();
}