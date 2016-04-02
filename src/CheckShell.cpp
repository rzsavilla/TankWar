#include "CheckShell.h"

CheckShell::CheckShell(TankControl* ptr_tank){
	shellSpotted = new ShellSpotted_Condition(ptr_tank);
	shellIntersect = new ShellIntersect_Condition(ptr_tank);
	canAvoid = new CanAvoid_Condition(ptr_tank);
	evade = new Evade_Action(ptr_tank);

	addChild(shellSpotted);
	addChild(shellIntersect);
	addChild(canAvoid);
	addChild(evade);
}

CheckShell::~CheckShell() {
	//Delete nodes instantiated with "new"
	delete shellSpotted;
	delete shellIntersect;
	delete canAvoid;
	delete evade;
}

///////////////////////Set tank pointer/////////////////////////////////
ShellSpotted_Condition::ShellSpotted_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

ShellIntersect_Condition::ShellIntersect_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

CanAvoid_Condition::CanAvoid_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

Evade_Action::Evade_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

/////////////Run Nodes/////////////////////////
bool ShellSpotted_Condition::run() {
	if (tank->spottedShell()) {
		std::cout << "Shell Spotted\n";
		return true;
	}
	else {
		return false;
	}
}

bool ShellIntersect_Condition::run() {
	//Returns true if shell will collide with tank
	std::cout << " Checking Shell Intersect\n";
	return true;
}

bool CanAvoid_Condition::run() {
	//Returns true if tank is able to evade shell
	std::cout << "  Checking if avoidable\n";
	return true;
}

bool Evade_Action::run() {
	//Tank Move to evade 
		//Set desired position that moves away from projectile path?
			//Then apply move
	std::cout << "    Evading!!!!\n";
	return true;
}