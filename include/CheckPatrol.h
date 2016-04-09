#ifndef CHECKPATROL_H
#define CHECKPATROL_H

#include "Action.h"


class BasesNotFound_Condition : public Condition {
public:
	BasesNotFound_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

class Reposition_Action : public Action {
private:
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

class CheckPatrol: public BehaviourTree::Selector{
private:
	Reposition_Action *reposition;
public:
	float dx, dy;
	CheckPatrol(TankControl* ptr_tank);
	~CheckPatrol();
};

#endif