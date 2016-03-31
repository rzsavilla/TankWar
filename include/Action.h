#ifndef ACTION_H
#define ACTION_H

#include "SmartTank.h"
#include "BehaviourTree.h"

class Action : public BehaviourTree::Node{
protected:
	SmartTank* tank;
};

class Condition : public BehaviourTree::Node {
protected:
	SmartTank* tank;
};

#endif