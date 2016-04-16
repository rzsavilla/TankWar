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
	//this->addChild(checkShoot);
	//this->addChild(maintainDistance);
	//this->addChild(checkShoot);
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
	float fEnemyDistance = getDistance(Position(tank->getX(), tank->getY()), tank->enemyCurrPos);
	std::cout << "Enemy Distance: " << fEnemyDistance << std::endl;
	//Predictive aim is unecessary when enemy is too close
	if (tank->bEnemyMoving && fEnemyDistance > 125.0f) {				//Check if enemy tank is moving
		//std::cout << "Predictive aim calculations\n";
		//Aim turret to predicted enemy position
		tank->setTurretDesiredPosition(tank->getEnemyPredictedPos());
	}
	else {	//Enemy Tank not moving/Is too close
		//std::cout << "Aiming\n";
		tank->setTurretDesiredPosition(tank->enemyCurrPos);		//Will aim at enemy curret position
	}
	tank->bFastRotation = true;		//Tank will rotate with turret
	if (!tank->willShellHitFreindlyBuildingBuilding()) { //Check for friendly fire
		tank->bShoot = true;				//Will shoot when on target
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