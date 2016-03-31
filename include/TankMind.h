#ifndef TANKMIND_H
#define TANKMIND_H

/*!
	Tank decision making is done here
*/

#include "EnemySpotted.h"
#include "CheckShell.h"

class TankMind: public SmartTank {
private:
	BehaviourTree::Selector *root;
	CheckEnemy *checkEnemy;
	CheckShell *checkShell;
public:
	TankMind();
	~TankMind();

	void createBehaviour();
	void move();
	
};

#endif