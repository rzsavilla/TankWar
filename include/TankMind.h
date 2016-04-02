#ifndef TANKMIND_H
#define TANKMIND_H

/*!
	Tank decision making is done here
	Will run create/store and run the decision tree
*/

#include "CheckShell.h"
#include "CheckEnemy.h"
#include "CheckEnemyBase.h"
#include "CheckPatrol.h"

class TankMind: public TankControl {
private:
	BehaviourTree::Selector *root = new BehaviourTree::Selector;
	CheckShell *checkShell = new CheckShell(this);
	CheckEnemy *checkEnemy = new CheckEnemy(this);
	CheckEnemyBase *checkEnemyBase = new CheckEnemyBase(this);
	CheckPatrol *checkPatrol = new CheckPatrol(this);
public:
	TankMind();
	~TankMind();

	void createBehaviour();
	void move();
};

#endif