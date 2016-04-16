#include "CheckAttack.h"
CheckAttack::CheckAttack(TankControl *tank_ptr) {
	canAttack = new CanAttack_Condition(tank_ptr);
	haveAmmo = new HaveAmmo_Condition(tank_ptr);
	chooseTarget = new ChooseTarget(tank_ptr);
	
	this->addChild(canAttack);
	this->addChild(haveAmmo);
	this->addChild(chooseTarget);
}

CheckAttack::~CheckAttack() {
	delete canAttack;
	delete haveAmmo;
	delete chooseTarget;
}

ChooseTarget::ChooseTarget(TankControl *tank_ptr) {
	checkEnemy = new CheckEnemy(tank_ptr);
	checkEnemyBase = new CheckEnemyBase(tank_ptr);

	this->addChild(checkEnemy);				//Attack enemy tank
	this->addChild(checkEnemyBase);			//Attack enemy base
}

ChooseTarget::~ChooseTarget() {
	delete checkEnemy;
	delete checkEnemyBase;
}

CanAttack_Condition::CanAttack_Condition(TankControl* tank_ptr) {
	this->tank = tank_ptr;
}

bool CanAttack_Condition::run() {
	if (tank->canFire()) {
		return true;
	}
	else {
		return false;
	}
}
