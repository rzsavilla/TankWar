#ifndef CHECKATTACK_H
#define CHECKATTACK_H

#include "CheckEnemy.h"
#include "CheckEnemyBase.h"
#include "CheckShoot.h"

class ChooseTarget : public  BehaviourTree::Selector {
private:
	CheckEnemy *checkEnemy;
	CheckEnemyBase *checkEnemyBase;
public:
	ChooseTarget(TankControl* ptr);
	~ChooseTarget();
};

class CheckAttack: public BehaviourTree::Sequence {
private:
	HaveAmmo_Condition *haveAmmo;
	ChooseTarget *chooseTarget;
public:
	CheckAttack(TankControl *ptr);
	~CheckAttack();
};

#endif