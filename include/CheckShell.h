/*!
	Actions and Conditions
*/

#ifndef CHECKSHELL_H
#define CHECKSHELL_H

#include "Action.h"

//////////Nodes Actions/Conditions/////////////////////
//! AI can see a shell
class ShellSpotted_Condition: public Condition {
public:
	ShellSpotted_Condition(TankControl *ptr_tank);
	bool firstSpot = true;
	virtual bool run() override;
};

class ShellIntersect_Condition: public Condition {
public:
	ShellIntersect_Condition(TankControl *ptr_tank);
	virtual bool run() override;
};

//! Calculations to check if shell can be avoided
class CanAvoid_Condition : public Condition{
public:
	CanAvoid_Condition(TankControl *ptr_tank);
	virtual bool run() override;
};

//! Move the tank away from shell path.
class Evade_Action : public Action {
public :
	Evade_Action(TankControl *ptr_tank);
	virtual bool run() override;
};

class CheckShell : public BehaviourTree::Sequence {
private:
	ShellSpotted_Condition *shellSpotted;
	ShellIntersect_Condition *shellIntersect;
	CanAvoid_Condition *canAvoid;
	Evade_Action *evade;
	
public:
	
	CheckShell(TankControl* ptr_tank); //!< Constructor
	~CheckShell();					   //!< Destructor, make sure you delete all pointers instanciated using "new"
	
};

#endif