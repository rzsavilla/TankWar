#include "CheckShoot.h"

CheckShoot::CheckShoot(TankControl *ptr_tank) {
	haveAmmo = new HaveAmmo_Condition(ptr_tank);
	hasLOS = new LOS_Condition(ptr_tank);
	aimTurret = new Aim_Action(ptr_tank);
	shoot = new Shoot_Action(ptr_tank);

	//Create branch
	//this->addChild(haveAmmo);
	this->addChild(hasLOS);
	this->addChild(aimTurret);
	this->addChild(shoot);
}

CheckShoot::~CheckShoot() {
	//Delete nodes instantiated with new
	delete haveAmmo;
	delete aimTurret;
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
	if (tank->getNumberOfShells() >0) {
		std::cout << "Have Ammo\n";
		return true;
	}
	else {
		return false;
	}
}

bool LOS_Condition::run() {
	std::cout << " Checking LOS\n";
	return true;
}

bool Aim_Action::run() {
	std::cout << "  Aiming\n";
	return true;
}

bool Shoot_Action::run() {
	std::cout << "   Shoot!!!!!\n";
	return true;
}