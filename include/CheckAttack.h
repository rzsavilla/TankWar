#ifndef CHECKATTACK_H
#define CHECKATTACK_H

#include "CheckEnemy.h"
#include "CheckEnemyBase.h"
#include "CheckShoot.h"

//! Check if tank is able to fire
class CanAttack_Condition : public Condition {
public:
	CanAttack_Condition(TankControl* tank_ptr);
	virtual bool run() override;
};

//! Tank will decide whether to attack either tank or base, prioritizing enemy tank
class ChooseTarget : public  BehaviourTree::Selector {
private:
	CheckEnemy *checkEnemy;
	CheckEnemyBase *checkEnemyBase;
public:
	ChooseTarget(TankControl* tank_ptr);
	~ChooseTarget();
};

//! Check conditions to attack before choosing a target to shoot at
class CheckAttack: public BehaviourTree::Sequence {
private:
	CanAttack_Condition *canAttack;
	HaveAmmo_Condition *haveAmmo;
	ChooseTarget *chooseTarget;
public:
	CheckAttack(TankControl *tank_ptr);
	~CheckAttack();
};

#endif