#ifndef CHECKENEMY_H
#define CHECKENEMY_H

#include "Action.h"
#include "CheckShoot.h"

//! Return true if enemy is found
class EnemySpotted_Condition: public Condition {
public:
	EnemySpotted_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

//! Calculates enemy tanks positon and sets target position
class PredictAim_Action : public Action {
public:
	PredictAim_Action(TankControl* ptr_tank);
	virtual bool run() override;
};

//! \class CheckEnemy Seqence node decision to attack enemy
class CheckEnemy: public BehaviourTree::Sequence {
private:
	EnemySpotted_Condition *enemySpotted;
	HaveAmmo_Condition *haveAmmo;
	PredictAim_Action *predictAim;
	CheckShoot *checkShoot;
public:
	CheckEnemy(TankControl *ptr_tank);
	~CheckEnemy();
};

#endif