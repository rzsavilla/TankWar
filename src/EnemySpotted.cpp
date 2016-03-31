#include "EnemySpotted.h"

CheckEnemy::CheckEnemy(SmartTank* ptr_tank)
	//Initializes constructors
	: tank(ptr_tank)
	, enemySpotted(new EnemySpotted_Condition(ptr_tank))
	, predictAim(new PredictiveAim_Action(ptr_tank))
	, aimAction(new Aim_Action(ptr_tank))
{
	//Build Tree - set Nodes in order
	addChild(enemySpotted);
	addChild(predictAim);
	addChild(aimAction);
}

CheckEnemy::~CheckEnemy() {
	delete aimAction;
	delete predictAim;
	delete enemySpotted;
}