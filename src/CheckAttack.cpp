#include "CheckAttack.h"

CheckAttack::CheckAttack(TankControl *ptr) {
	haveAmmo = new HaveAmmo_Condition(ptr);
	chooseTarget = new ChooseTarget(ptr);
	
	this->addChild(haveAmmo);
	this->addChild(chooseTarget);
}

CheckAttack::~CheckAttack() {
	delete haveAmmo;
	
}

ChooseTarget::ChooseTarget(TankControl *ptr) {
	checkEnemy = new CheckEnemy(ptr);
	checkEnemyBase = new CheckEnemyBase(ptr);

	this->addChild(checkEnemy);
	this->addChild(checkEnemyBase);
}

ChooseTarget::~ChooseTarget() {
	delete checkEnemy;
	delete checkEnemyBase;
}