/*
	Inherited by nodes for abstraction.
*/

#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "TankControl.h"
#include "BehaviourTree.h"

class Action : public BehaviourTree::Node{
protected:
	TankControl* tank;
public:
	Action() {

	}
	Action(TankControl *ptr_tank) {
		tank = ptr_tank;
	}
};

class Condition : public BehaviourTree::Node {
protected:
	TankControl* tank;
public:
	Condition() {

	}
	Condition(TankControl *ptr_tank) {
		tank = ptr_tank;
	}
};

#endif