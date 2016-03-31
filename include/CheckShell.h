/*!
	Actions and Conditions
*/

#ifndef CHECKSHELL_H
#define CHECKSHELL_H

#include <iostream>
#include "Action.h"

/*
Forward Declare all Action/Condition classes
	class myClass;
*/

class CanAvoidCondition; //Forward Declaration

class CheckShell : public BehaviourTree::Sequence {
private:
	//Actions or conditions object pointers here
	CanAvoidCondition *canAvoid;
public:
	CheckShell(SmartTank* ptr_tank); //Constructor
	~CheckShell();					 //Destructor, make sure you delete all pointers instanciated using "new"
};

class CanAvoidCondition : public Condition {
public:
	CanAvoidCondition(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}

	virtual bool run() override{
		//Check if projectile is oncoming
		return false;
	}
};



#endif