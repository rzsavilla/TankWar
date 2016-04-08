#ifndef CHECKENEMY_H
#define CHECKENEMY_H

#include "Action.h"
#include "CheckShoot.h"
#include "CheckPatrol.h"

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

//! Checks if enemy tank is too close
class EnemyTooClose_Condition : public Condition{
public:
	EnemyTooClose_Condition(TankControl* ptr_tank);
	virtual bool run() override;
};

//! Moves away if enemy is too close
class MoveAway_Action : public Action {
public:
	MoveAway_Action(TankControl* ptr_tank);
	virtual bool run() override;
};

//! \class MaintainDistance Sequence node to keep distance from enemy
class MaintainDistance : public BehaviourTree::Sequence {
	EnemyTooClose_Condition *enemyTooClose;
	MoveAway_Action *moveAway;
	Reposition_Action *reposition;
public:
	MaintainDistance(TankControl *ptr_tank);
	~MaintainDistance();
};

//! \class CheckEnemy Seqence node decision to attack enemy
class CheckEnemy: public BehaviourTree::Sequence {
private:
	EnemySpotted_Condition *enemySpotted;
	HaveAmmo_Condition *haveAmmo;
	PredictAim_Action *predictAim;
	CheckShoot *checkShoot;
	MaintainDistance *maintainDistance;
public:
	CheckEnemy(TankControl *ptr_tank);
	~CheckEnemy();
};

#endif