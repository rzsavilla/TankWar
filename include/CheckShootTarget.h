#pragma once

#include "Action.h"

class LOS_Condition;
class Aiming_Turret;
class Shoot_Target;

class ShootCheck : public BehaviourTree::Sequence {
private:
	SmartTank *tank;
	LOS_Condition *hasLOS;
	//Shoot_Target *shootTarget;
	Aiming_Turret *aimTurret;
public:
	ShootCheck(SmartTank* ptr_tank);
	~ShootCheck();

};


//////////////////////////////////Nodes
class LOS_Condition : public Condition {
public:
	LOS_Condition(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}
	virtual bool run() override {
		if (tank->bEnemySpotted){
			std::cout << "I see the target. \n";
			return true;
		}
		else {
			return false;
		}
	}
};

class Aiming_Turret : public Action {
public:
	Aiming_Turret(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}
	virtual bool run() override {
		std::cout << "Aiming towards target. \n";
		return true;
	}
};

class Shoot_Action : public Action {
public:
	Shoot_Action(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}
	virtual bool run() override {
		std::cout << "Shooting. \n";
		return true;
	}
};
