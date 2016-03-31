#include "EnemySpotted.h"

CheckEnemy::CheckEnemy(SmartTank* ptr_tank)
	//Initializes constructors
	: tank(ptr_tank)
	, enemySpotted(new EnemySpotted_Condition(ptr_tank))
	, aimAction(new Aim_Action(ptr_tank))
	, enemyMoving(new IsEnemyMoving(ptr_tank))
{
	addChild(enemySpotted);
	addChild(aimAction);
	addChild(enemyMoving);
}

CheckEnemy::~CheckEnemy() {
	delete aimAction;
	delete enemyMoving;
	delete enemySpotted;
}

IsEnemyMoving::IsEnemyMoving(SmartTank* ptr_tank)
	: predictAim(new PredictAimAction(ptr_tank))
{
	addChild(predictAim);
}

IsEnemyMoving::~IsEnemyMoving() {
	delete predictAim;
}

