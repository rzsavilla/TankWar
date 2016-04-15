#include "CheckEnemyBase.h"

CheckEnemyBase::CheckEnemyBase(TankControl *ptr_tank) {
	isWinning = new Winning_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	targetBase = new TargetBase_Action(ptr_tank);

	addChild(isWinning);
	addChild(targetBase);
}

CheckEnemyBase::~CheckEnemyBase() {

}

Winning_Condition::Winning_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

TargetBase_Action::TargetBase_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

bool Winning_Condition::run() {
	if (tank->bEnemyBaseSpotted && tank->iMyScore > tank->iEnemyScore) {
		std::cout << "Is winning";
		return true;
	}
	else {
		return false;
	}
}

bool TargetBase_Action::run() {
	std::cout << "Attack Enemy base\n";
	tank->setTurretDesiredPosition(tank->vEnemyBasePos.back());

	if (tank->bTurretOnTarget) {		//Shoot when tank is aimed at target
		tank->bShoot = true;
	}

	return true;
}