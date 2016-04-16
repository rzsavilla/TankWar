#include "CheckPatrol.h"

CheckPatrol::CheckPatrol(TankControl *ptr_tank) {
	reposition = new Reposition_Action(ptr_tank);
	addChild(reposition);
}

CheckPatrol::~CheckPatrol() {
	delete reposition;
}

FindBases::FindBases(TankControl* ptr_tank) {

}

FindBases::~FindBases() {

}

BasesNotFound_Condition::BasesNotFound_Condition(TankControl * ptr_tank) {
	this->tank = ptr_tank;
}

Reposition_Action::Reposition_Action(TankControl * ptr_tank) {
	this->tank = ptr_tank;
	fX = 0.0f;
	fY = 0.0f;
}

bool Reposition_Action::run() {
	if (tank->reachedDesiredPos() || tank->hasCollided()) {			// When tank should reposition
		tank->bIsMoving = false;
		if (tank->hasCollided()) { tank->goBackward(); }			// Move away from collision slightly
		std::cout << "Reposition\n";
	}

	if (!tank->bIsMoving) {						//Reposition tank
		fX = (float)(rand() % 750 + 10);		//Generate random position
		fY = (float)(rand() % 540 + 10);
		//std::cout << "Repositioning\n";
		tank->bIsMoving = true;					//Tank has is now moving
	}
	tank->patrolTurret();
	tank->setDesiredPosition(fX, fY);
	return true;
}

bool BasesNotFound_Condition::run() {
	if (tank->vBasePos.size() >= tank->iNumBases + tank->iNumEnemyBases) {
		//All bases found
		return true;
	}

	return false;
}