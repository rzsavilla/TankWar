#include "CheckShell.h"

CheckShell::CheckShell(TankControl* ptr_tank){
	shellSpotted = new ShellSpotted_Condition(ptr_tank);
	shellIntersect = new ShellIntersect_Condition(ptr_tank);
	canAvoid = new CanAvoid_Condition(ptr_tank);
	evade = new Evade_Action(ptr_tank);
	rotateToEnemy = new RotateToEnemy(ptr_tank);

	addChild(shellSpotted);
	addChild(shellIntersect);
	addChild(canAvoid);
	addChild(evade);
	addChild(rotateToEnemy);
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
			tank->shellSeenAt = tank->shellCurrPos;
			firstSpot = false;
		}
		tank->shellWasSeenLookingForSource = false;
		return true;
	}
	else {
		if (tank->shellWasSeenLookingForSource)
		{
			return true;
		}
		firstSpot = true;
		return false;
		
	}
}

bool ShellIntersect_Condition::run() {
	//Returns true if shell will collide with tank
	if (tank->shellWasSeenLookingForSource)
	{
		return true;
	}
	if (tank->willShellHit(tank->shellCurrPos, tank->shellPrevPos))
	{
		std::cout << " Will hit\n";
		tank->bIsDodging = true;
		return true;
		
	}
	//std::cout << " wont hit\n";
	tank->bIsDodging = false;
	tank->shellWasSeenLookingForSource = true;
	return false;
	
}

bool CanAvoid_Condition::run() {
	if (tank->shellWasSeenLookingForSource)
	{
		return true;
	}

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

	if (tank->shellWasSeenLookingForSource)
	{
		return true;
	}
	//Tank Move to evade 
		//Set desired position that moves away from projectile path?
			//Then apply move
	//std::cout << "    Evading!!!!\n";
	cout << "Dodge" << endl;
	tank->evadeShell();
	if (tank->reachedDesiredPos())
	{
		tank->bIsDodging = false;
		return true;
	}
	
}


RotateToEnemy::RotateToEnemy(TankControl* ptr_tank) {
	this->tank = ptr_tank;
}

bool RotateToEnemy::run() {
	
	tank->shellWasSeenLookingForSource = true;
	tank->setDesiredPosition(tank->shellSeenAt);
	tank->setTurretDesiredPosition(tank->shellSeenAt);
	//tank->bFastRotation = true;

	if (tank->bEnemySpotted) {
		std::cout << "Enemy Spotted\n";
		tank->setTurretDesiredPosition(tank->enemyCurrPos);			//Execute Action
		return false;
	}

	if (tank->reachedDesiredPos())
	{
		tank->shellWasSeenLookingForSource = false;
		std::cout << "Look for enemy\n";
		if (tank->bEnemySpotted) {
			std::cout << "Enemy Spotted\n";
			tank->setTurretDesiredPosition(tank->enemyCurrPos);			//Execute Action
			
			return false;
		}
		else {
			return true;	//No enemy spotted action was not executed
		}
	}

	return true;
	
	
}