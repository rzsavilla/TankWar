#include "CheckAttack.h"

CheckAttack::CheckAttack(TankControl *ptr) {
	haveAmmo = new HaveAmmo_Condition(ptr);
	chooseTarget = new ChooseTarget(ptr);
	
	this->addChild(haveAmmo);
	this->addChild(chooseTarget);
}

CheckAttack::~CheckAttack() {
	delete haveAmmo;
	delete chooseTarget;
}

ChooseTarget::ChooseTarget(TankControl *ptr) {
	checkEnemy = new CheckEnemy(ptr);
	checkEnemyBase = new CheckEnemyBase(ptr);

	this->addChild(checkEnemy);				//Attack enemy tank
	this->addChild(checkEnemyBase);			//Attack enemy base
}

ChooseTarget::~ChooseTarget() {
	delete checkEnemy;
	delete checkEnemyBase;
}