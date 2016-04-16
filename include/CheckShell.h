/*!
	Actions and Conditions
*/

#ifndef CHECKSHELL_H
#define CHECKSHELL_H

#include "Action.h"
#include "CheckEnemy.h"
#include "CheckShoot.h"

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

//! Will rotate turret towards enemy
class RotateToEnemy : public Action {
public:
	RotateToEnemy(TankControl* ptr_tank);		//<! Default Constructor initialize nodes and create branch
	virtual bool run() override;
};

/*!	
	Tank will aim turret towards enemy it spots
*/
class LookAtEnemy : public BehaviourTree::Succeeder{
private:
	RotateToEnemy* rotateToEnemy;		//!< Single Child node will never fail
public:
	LookAtEnemy(TankControl* ptr_tank);	//!< Default Constructor
	~LookAtEnemy();		//!< Destructor
};

//! Branch checks for shell, if shell will collide, tank will attempt to dodge
class CheckShell : public BehaviourTree::Sequence {
private:
	ShellSpotted_Condition *shellSpotted;
	ShellIntersect_Condition *shellIntersect;
	CanAvoid_Condition *canAvoid;
	Evade_Action *evade;
	RotateToEnemy *rotateToEnemy;	//!< Node will always return true when run
public:
	CheckShell(TankControl* ptr_tank); //!< Constructor
	
	~CheckShell();					   //!< Destructor, make sure you delete all pointers instanciated using "new"
};

#endif