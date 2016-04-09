#include "CheckEnemy.h"

CheckEnemy::CheckEnemy(TankControl *ptr_tank) {
	enemySpotted = new EnemySpotted_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	predictAim = new PredictAim_Action(ptr_tank);
	checkShoot = new CheckShoot(ptr_tank);
	maintainDistance = new MaintainDistance(ptr_tank);

	this->addChild(enemySpotted);
	this->addChild(haveAmmo);
	this->addChild(predictAim);
	this->addChild(checkShoot);
	this->addChild(maintainDistance);
}

CheckEnemy::~CheckEnemy() {
	delete enemySpotted;
	delete haveAmmo;
	delete predictAim;
	delete checkShoot;
}

MaintainDistance::MaintainDistance(TankControl *ptr_tank) {
	enemyTooClose = new EnemyTooClose_Condition(ptr_tank);
	moveAway = new MoveAway_Action(ptr_tank);
	reposition = new Reposition_Action(ptr_tank);

	this->addChild(enemyTooClose);
	//	this->addChild(moveAway);
	this->addChild(reposition);
}

MaintainDistance::~MaintainDistance() {
	delete enemyTooClose;
	delete moveAway;
	delete reposition;
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

EnemyTooClose_Condition::EnemyTooClose_Condition(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

MoveAway_Action::MoveAway_Action(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

bool EnemyTooClose_Condition::run() {
	float fDist;

	if (!tank->canFire()) {
		fDist = distance(tank->enemyCurrPos.getX(), tank->getX(), tank->enemyCurrPos.getY(), tank->getY());
		std::cout << fDist << std::endl;
		if (fDist < 150.f) {
			std::cout << "Move Away\n";
			return true;
		}
	}

	return false;
}


bool MoveAway_Action::run() {
	std::cout << "Moving Away\n\n\n\n";

	return true;
}