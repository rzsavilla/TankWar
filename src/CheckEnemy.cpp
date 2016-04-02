#include "CheckEnemy.h"

CheckEnemy::CheckEnemy(TankControl *ptr_tank) {
	enemySpotted = new EnemySpotted_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	predictAim = new PredictAim_Action(ptr_tank);
	checkShoot = new CheckShoot(ptr_tank);

	this->addChild(enemySpotted);
	this->addChild(haveAmmo);
	this->addChild(predictAim);
	this->addChild(checkShoot);
}

CheckEnemy::~CheckEnemy() {
	delete enemySpotted;
	delete haveAmmo;
	delete predictAim;
	delete checkShoot;
}

EnemySpotted_Condition::EnemySpotted_Condition(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

PredictAim_Action::PredictAim_Action(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

bool EnemySpotted_Condition::run() {
	if (tank->spottedEnemy()) {
		std::cout << "Enemy Spotted\n";
		return true;
	}
	else {
		return false;
	}
}

bool PredictAim_Action::run() {
	std::cout << "Predictive aim calculations\n";
	//set aim position
	tank->setTurretDesiredPosition(tank->enemyCurrPos);	//Rotate Turret towards enemy
	tank->setDesiredPosition(tank->enemyCurrPos);		//Tank will rotate towards enemy then move forward
	return true;
}
