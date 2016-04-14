#ifndef CHECKENEMYBASE_H
#define CHECKENEMYBASE_H

#include "Action.h"
#include "CheckShoot.h"

class Winning_Condition: public Condition {
public:
	Winning_Condition(TankControl *ptr_tank);
	virtual bool run() override;
};

//! Looks for the closest enemy base, sets it as a target
class TargetBase_Action : public Action {
public:
	TargetBase_Action(TankControl *ptr_tank);
	virtual bool run() override;
};

class CheckEnemyBase: public BehaviourTree::Sequence {
private:
	Winning_Condition *isWinning;
	HaveAmmo_Condition *haveAmmo;
	TargetBase_Action *targetBase;
	CheckShoot *checkShoot;
public:
	CheckEnemyBase(TankControl *ptr);
	~CheckEnemyBase();
};



#endif