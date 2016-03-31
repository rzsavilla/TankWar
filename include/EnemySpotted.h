/*!
	AI Spots Enemy
*/
#ifndef ENEMYSPOTTED_H
#define ENEMYSPOTTED_H

#include <iostream>
#include "Action.h"

//Class forward declaration
class EnemySpotted_Condition;
class IsEnemyMoving;
class Aim_Action;

class CheckEnemy : public BehaviourTree::Sequence {
private:
	//Object pointers
	SmartTank *tank;
	EnemySpotted_Condition *enemySpotted;
	Aim_Action *aimAction;
	IsEnemyMoving *enemyMoving;
public:
	CheckEnemy(SmartTank* ptr_tank);
	~CheckEnemy();
};

//////////////////Nodes/////////////////////////////
class EnemySpotted_Condition: public Condition {
public:
	EnemySpotted_Condition(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}

	virtual bool run() override {
		if (tank->bEnemySpotted) {
			std::cout << "Enemy Spotted\n";
			return true;
		}
		else {
			return false;
		}
	}
};


//Rotate Turret towards enemy tank/predicted aim position
class Aim_Action : public Action{
public:
	Aim_Action(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}

	virtual bool run() override{
		if (tank->bEnemySpotted) {
			//Aim towards to enemy/target
			std::cout << "Aim\n";
			return true;
		}
		else {
			return false;
		}
	}
};

//Class Forward Declaration
class PredictAimAction;

class IsEnemyMoving: public BehaviourTree::Sequence {
private:
	SmartTank *tank;
	PredictAimAction *predictAim;
public:
	IsEnemyMoving(SmartTank* ptr_tank);
	~IsEnemyMoving();
};

//Predictive aiming
class PredictAimAction : public Action {
public:
	PredictAimAction(SmartTank* ptr_tank) {
		this->tank = ptr_tank;
	}

	virtual bool run() override {
		//Calculate Predictive Aim here
			//Set Predicted location
		return true;
	}
};

#endif
