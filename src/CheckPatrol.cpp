#include "CheckPatrol.h"

CheckPatrol::CheckPatrol(TankControl *ptr_tank) {
	reposition = new Reposition_Action(ptr_tank);
	float dx, dy;
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
	dx = 0.f;
	dy = 0.f;
}

bool Reposition_Action::run() {
	if (tank->tankReachedDestination()) {
		tank->isMoving = false;
		std::cout << "Reached Position\n";
	}
	if (!tank->isMoving) {
		dx = (float)(rand() % 750 + 10);
		dy = (float)(rand() % 540 + 10);
		std::cout << "Repositioning\n";
		tank->isMoving = true;
		}
	tank->setDesiredPosition(dx, dy);
	return true;
}

bool BasesNotFound_Condition::run() {
	if (tank->vBasePos.size() >= tank->iNumBases + tank->iNumEnemyBases) {
		//All bases found
		return true;
	}
	std::cout << "Looking for bases\n";
	return false;
}