///*!
//	AI Spots Enemy
//*/
//#ifndef ENEMYSPOTTED_H
//#define ENEMYSPOTTED_H
//
//#include <iostream>
//#include "Action.h"
//
////Class forward declaration
//class EnemySpotted_Condition;
//class Aim_Action;
//class PredictiveAim_Action;
//
//class CheckEnemy : public BehaviourTree::Sequence {
//private:
//	//Object pointers
//	TankControl *tank;
//	EnemySpotted_Condition *enemySpotted;
//	Aim_Action *aimAction;
//	PredictiveAim_Action *predictAim;
//public:
//	CheckEnemy(TankControl* ptr_tank);
//	~CheckEnemy();
//};
//
////////////////////Nodes/////////////////////////////
//class EnemySpotted_Condition: public Condition {
//public:
//	EnemySpotted_Condition(TankControl* ptr_tank) :Condition(ptr_tank){
//		this->tank = ptr_tank;
//	}
//	virtual bool run() override {
//		if (tank->spottedEnemy()) {
//			std::cout << "Enemy Spotted\n";
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//};
//
////Calculate enemy predicted position
//class PredictiveAim_Action : public Action {
//public:
//	PredictiveAim_Action(TankControl* ptr_tank): Action(ptr_tank){
//
//	}
//	virtual bool run() override {
//		//Predictive calculatesion here
//			//Set Predicted target position
//		tank->predictedEnemyPos = tank->enemyCurrPos;
//		return true;
//	}
//};
//
//
////Rotate Turret towards enemy tank/predicted aim position
//class Aim_Action : public Action{
//public:
//	Aim_Action(TankControl* ptr_tank) {
//		this->tank = ptr_tank;
//	}
//
//	virtual bool run() override{
//		if (tank->spottedEnemy()) {
//			//Aim towards to enemy/target
//			tank->m_rotateTurretTowards(tank->predictedEnemyPos);
//			std::cout << "Aim\n";
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//};
//
//#endif
