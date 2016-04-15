#include "CheckShell.h"

CheckShell::CheckShell(TankControl* ptr_tank){
	shellSpotted = new ShellSpotted_Condition(ptr_tank);
	shellIntersect = new ShellIntersect_Condition(ptr_tank);
	canAvoid = new CanAvoid_Condition(ptr_tank);
	evade = new Evade_Action(ptr_tank);
	lookAtEnemy = new LookAtEnemy(ptr_tank);

	addChild(shellSpotted);
	addChild(shellIntersect);
	addChild(canAvoid);
	addChild(evade);
	addChild(lookAtEnemy);
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
		if (firstSpot)
		{
			tank->setTurretDesiredPosition(tank->shellCurrPos);
			firstSpot = false;
		}
		
		///std::cout << "Shell Spotted\n";
		return true;
	}
	else {
		return false;
		firstSpot = true;
	}
}

bool ShellIntersect_Condition::run() {
	//Returns true if shell will collide with tank
	
	if (tank->willShellHit(tank->shellCurrPos, tank->shellPrevPos))
	{
		std::cout << " Will hit\n";
		return true;
		
	}
	//std::cout << " wont hit\n";
	tank->bIsDodging = false;
	return false;
	
}

bool CanAvoid_Condition::run() {
	//Returns true if tank is able to evade shell
	//std::cout << "  Checking if avoidable\n";
	if (tank->checkShellProximity() || this->tank->bIsDodging)
	{
		//std::cout << "Avoidable\n";
		return true;
		
	}
	else
	{
		//std::cout << "Un avoidable\n";
		return false;
	}
	
}

bool Evade_Action::run() {
	//Tank Move to evade 
		//Set desired position that moves away from projectile path?
			//Then apply move
	//std::cout << "    Evading!!!!\n";
	cout << "Dodge" << endl;
	tank->evadeShell();
	if (tank->reachedDesiredPos())
	{
		tank->bIsDodging = false;
	}
	return true;
}

LookAtEnemy::LookAtEnemy(TankControl* ptr_tank) {
	rotateToEnemy = new RotateToEnemy(ptr_tank);
	this->setChild(rotateToEnemy);
}

LookAtEnemy::~LookAtEnemy() {
	delete rotateToEnemy;
}

RotateToEnemy::RotateToEnemy(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

bool RotateToEnemy::run() {
	std::cout << "Look for enemy\n";
	if (tank->bEnemySpotted) {
		std::cout << "Enemy Spotted\n";
		tank->setTurretDesiredPosition(tank->enemyCurrPos);			//Execute Action
		return true;
	}
	false;	//No enemy spotted action was not executed
}