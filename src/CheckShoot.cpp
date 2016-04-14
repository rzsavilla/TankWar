#include "CheckShoot.h"

CheckShoot::CheckShoot(TankControl *ptr_tank) {
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	hasLOS = new LOS_Condition(ptr_tank);
	shoot = new Shoot_Action(ptr_tank);

	//Create branch
	this->addChild(haveAmmo);
	this->addChild(hasLOS);
	this->addChild(shoot);
}

CheckShoot::~CheckShoot() {
	//Delete nodes instantiated with new
	delete haveAmmo;
	delete hasLOS;
	delete shoot;
}

HaveAmmo_Condition::HaveAmmo_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

LOS_Condition::LOS_Condition(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

Aim_Action::Aim_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

Shoot_Action::Shoot_Action(TankControl *ptr_tank) {
	this->tank = ptr_tank;
}

bool HaveAmmo_Condition::run() {
	if (tank->getNumberOfShells() > 0) {
		std::cout << "Have Ammo\n";
		return true;
	}
	else {
		std::cout << "No Ammo\n";
		return false;
	}
}

bool LOS_Condition::run() {
	std::cout << " Checking LOS\n";
	if (tank->bTurretOnTarget && tank->willShellHitFreindlyBuilding() == false) {
		
		return true;					//Turret is aimed
	}
	else {
		return false;
	}
}

bool Aim_Action::run() {
	if (tank->getNumberOfShells() > 0) {
		//std::cout << "Have Ammo\n";
		return true;
	}
	else {
		return false;
	}
}

bool Shoot_Action::run() {
	std::cout << "   Shoot!!!!!\t" << tank->bHasTurretDesiredPos << std::endl;
	tank->bShoot = true;					//Tank will fire projectile
	return true;
}