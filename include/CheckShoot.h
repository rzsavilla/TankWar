#ifndef CHECKSHOOT_H
#define CHECKSHOOT_H

#include "Action.h"

//////////////////////////////////Nodes//////////////////////////
class HaveAmmo_Condition : public Condition {
public:
	HaveAmmo_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

class LOS_Condition : public Condition {
public:
	LOS_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

//! Rotate towards target position
class Aim_Action : public Action {
public:
	Aim_Action(TankControl* ptr_tank);
	virtual bool run() override;
};

class Shoot_Action : public Action {
public:
	Shoot_Action(TankControl* ptr_tank);
	virtual bool run() override;
};

class CheckShoot : public BehaviourTree::Sequence {
private:
	HaveAmmo_Condition *haveAmmo;
	LOS_Condition *hasLOS;
	Shoot_Action *shoot;
public:
	CheckShoot(TankControl* ptr_tank);
	~CheckShoot();
};

#endif