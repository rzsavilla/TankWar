#include "CheckEnemyBase.h"
#include "Calculations.h"

CheckEnemyBase::CheckEnemyBase(TankControl *ptr_tank) {
	isWinning = new Winning_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	targetBase = new TargetBase_Action(ptr_tank);
	checkShoot = new CheckShoot(ptr_tank);

	addChild(isWinning);
	addChild(targetBase);
	//addChild(checkShoot);
}

CheckEnemyBase::~CheckEnemyBase() {
	delete isWinning;
	delete haveAmmo;
	delete targetBase;
	delete checkShoot;
}

Winning_Condition::Winning_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

TargetBase_Action::TargetBase_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

bool Winning_Condition::run() {
	if (tank->bEnemyBaseSpotted && tank->iMyScore < tank->iEnemyScore + 50) {
		std::cout << "Is winning" << endl;;
		return true;
	}
	else {
		return false;
	}
}

bool TargetBase_Action::run() {
	std::cout << "Attack Enemy base\n";
	tank->setTurretDesiredPosition(tank->enemyBasePos.getX(), tank->enemyBasePos.getY());
	tank->bFastRotation = true;
	tank->bShoot = true;
	return true;
}