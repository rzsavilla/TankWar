#include "CheckEnemyBase.h"
#include "Calculations.h"

CheckEnemyBase::CheckEnemyBase(TankControl *ptr_tank) {
	enemyBaseSpotted = new EnemyBaseSpotted_Condition(ptr_tank);
	isWinning = new Winning_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	targetBase = new TargetBase_Action(ptr_tank);

	//Add Nodes to sequence all nodes must succeed else sequence fails
	addChild(enemyBaseSpotted);
	addChild(isWinning);
	addChild(targetBase);
}

CheckEnemyBase::~CheckEnemyBase() {
	delete enemyBaseSpotted;
	delete isWinning;
	delete haveAmmo;
	delete targetBase;
}

EnemyBaseSpotted_Condition::EnemyBaseSpotted_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

Winning_Condition::Winning_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

TargetBase_Action::TargetBase_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

bool EnemyBaseSpotted_Condition::run() {
	if (tank->bEnemyBaseSpotted) {
		std::cout << "Enemy Base Spotted\n";
		return true;
	}
	else {
		return false;
	}
}

bool Winning_Condition::run() {
	std::cout << " Check if Winning\n";
	if (tank->iMyScore > tank->iEnemyScore + 50.0f) {
		std::cout << "  Winning\n";
		return true;
	}
	return false;		//Node Fails
}

bool TargetBase_Action::run() {
	std::cout << "   Attack Enemy base\n";
	tank->setTurretDesiredPosition(tank->enemyBasePos.getX(), tank->enemyBasePos.getY());
	tank->bFastRotation = true;
	if (tank->bTurretOnTarget) {
			tank->bShoot = true;
	}
	return true;
}