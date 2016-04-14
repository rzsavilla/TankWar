#include "CheckEnemy.h"

CheckEnemy::CheckEnemy(TankControl *ptr_tank) {
	enemySpotted = new EnemySpotted_Condition(ptr_tank);
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	predictAim = new PredictAim_Action(ptr_tank);
	checkShoot = new CheckShoot(ptr_tank);
	maintainDistance = new MaintainDistance(ptr_tank);

	this->addChild(enemySpotted);
	//this->addChild(haveAmmo);
	this->addChild(predictAim);
	this->addChild(checkShoot);
	//this->addChild(maintainDistance);
}

CheckEnemy::~CheckEnemy() {
	delete enemySpotted;
	delete haveAmmo;
	delete predictAim;
	delete checkShoot;
	delete maintainDistance;
}

MaintainDistance::MaintainDistance(TankControl *ptr_tank) {
	enemyTooClose = new EnemyTooClose_Condition(ptr_tank);
	moveAway = new MoveAway_Action(ptr_tank);
	reposition = new Reposition_Action(ptr_tank);

	this->addChild(enemyTooClose);
	// Add check if tank can shoot
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
		tank->bTurretOnTarget = false;
		return false;
	}
}

bool PredictAim_Action::run() {
	if (tank->bEnemyMoving) {				//Check if enemy tank is moving
		std::cout << "Predictive aim calculations\n";
		//Aim turret to predicted enemy position
		tank->setTurretDesiredPosition(tank->getEnemyPredictedPos());
		tank->bFastRotation = true;
	}
	else {
		std::cout << "Aiming\n";
		//Enemy Tank not moving
		tank->setTurretDesiredPosition(tank->enemyCurrPos);		//Will aim at enemy curret position
		tank->bFastRotation = true;
	}
	return true;
}

EnemyTooClose_Condition::EnemyTooClose_Condition(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

MoveAway_Action::MoveAway_Action(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

bool EnemyTooClose_Condition::run() {
	float fDist = 0.0f;

	if (!tank->canFire()) {
		//fDist = getDistance(tank->enemyCurrPos.getX(), tank->getX(), tank->enemyCurrPos.getY(), tank->getY());
		//std::cout << fDist << std::endl;
		//if (fDist < 150.f) {
		//	std::cout << "Move Away\n";
		//	return true;
		//}
		return true;
	}

	return false;
}


bool MoveAway_Action::run() {
	std::cout << "Moving Away\n\n\n\n";

	return true;
}