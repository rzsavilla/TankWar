#ifndef CHECKPATROL_H
#define CHECKPATROL_H

#include "Action.h"

class ShellNotSpotted_Condition : public Condition{
public:
	ShellNotSpotted_Condition(TankControl* ptr_tank);
	virtual bool run() override;

};

class BasesNotFound_Condition : public Condition {
public:
	BasesNotFound_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

class Reposition_Action : public Action {
private:
	bool bOneTime = true;
	float fX;
	float fY;
public:
	Reposition_Action(TankControl* ptr_tank);
	virtual bool run() override;
};

class FindBases : public BehaviourTree::Sequence {
private:

public:
	FindBases(TankControl* ptr_tank);
	~FindBases();
};

class CheckPatrol: public BehaviourTree::Sequence{
private:
	ShellNotSpotted_Condition * shellNotSpotted;
	Reposition_Action *reposition;
public:
	float dx, dy;
	CheckPatrol(TankControl* ptr_tank);
	~CheckPatrol();
};

#endif