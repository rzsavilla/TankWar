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
}

bool Reposition_Action::run() {
	std::cout << "Repositioning\n";
	tank->goForward();
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