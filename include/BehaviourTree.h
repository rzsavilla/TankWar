/*
	Code from
	http://www.cplusplus.com/forum/general/141582/

	other resources
	http://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php
	http://guineashots.com/2014/07/25/an-introduction-to-behavior-trees-part-1/
*/

/*!
	\file BehaviourTree.h
	\brief Declare behaviour tree nodes
*/

#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H

#include <vector>
#include <algorithm>

class BehaviourTree {
public:
	class Node {
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node{
	private:
		std::vector<Node*> children;
	public:
		const std::vector<Node*>& getChildren() const;
		void addChild(Node* child);
		void addChildren(std::initializer_list<Node*>&& newChildren);
		template <typename CONTAINER>
		void addChildren(const CONTAINER& newChildren);
	protected:
		std::vector<Node*> childrenShuffled() const;
	};

	class Selector : public CompositeNode {
	public:
		virtual bool run() override;
	};

	class Sequence : public CompositeNode {
	public:
		virtual bool run() override;
	};

	class Root : public Node {
	private:
		Node* child;										//!< Stoes pointer to the starting node
		friend class BehaviourTree;						//!< Gives access to BehaviourTree classes/elements
	public:
		void setChild(Node* newChild);				//!< Set Root Node
		virtual bool run() override;
	};

private:
	Root* root;			//!< Root of the Tree/Starts here
public:
	//Constructor
	BehaviourTree();
	void setRootChild(Node* rootChild) const;
	virtual bool run() const;
};

#endif