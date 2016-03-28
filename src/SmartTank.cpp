#include "SmartTank.h"

SmartTank::SmartTank() {
	
}

/////////////////State Functions/////////////////
void SmartTank::m_Idle() {
	m_CurrentState = State::Patrol;
}

void SmartTank::m_Patrol() {

}

void SmartTank::m_Evade(){

}

void SmartTank::m_Attack() {

}

void SmartTank::m_Update() {
	if (m_bShellSpotted) {
		//Check if oncoming
			//Evade
		//else ignore

		//Trace bullet
			//Set predicted enemy pos
	}
	if (m_bEnemySpotted) {
		//Calculate enemy heading
		m_DesiredPos = m_EnemyCurrPos;
		m_bHasDesiredPos = true;
		//Track enemy 
			//Fast rotate towards enemy
	}
	if (m_bBaseSpotted) {

	}
	if (m_bEnemyBaseSpotted) {

	}
}

//////////////////////Calculations/////////////////
float SmartTank::m_rotationDifference(Position pos,Position targetPos) {
	//Calculate Angle between two points
	float deltaX = pos.getX() - targetPos.getX();
	float deltaY = pos.getY() - targetPos.getY();
	float rad = atan2(deltaY, deltaX);
	float deg = (rad * (180 / PI)) + 180;
	float fDist = (deg - pos.getTh());;	//Rotation Distance

	//std::cout << "Diff: " << deg << "\t" << "this: " << pos.getTh() << "\t" << "Other:" << deg << "\n";

	if (fabs(fDist) > 180) {		//Ensures full rotation 359 <-> 0, shortest distance
		fDist = 0 - fDist;
	}
	return fDist;		//Returns positive or negative value (Right Or Left)
}

float SmartTank::m_rotationDifference(Position pos, float heading, Position targetPos) {
	//Calculate Angle between two points
	float deltaX = pos.getX() - targetPos.getX();
	float deltaY = pos.getY() - targetPos.getY();
	float rad = atan2(deltaY, deltaX);
	float deg = (rad * (180 / PI)) + 180;
	float fDist = (deg - heading);;	//Rotation Distance

	//std::cout << "Diff: " << deg << "\t" << "this: " << pos.getTh() << "\t" << "Other:" << deg << "\n";

	if (fabs(fDist) > 180) {		//Ensures full rotation 359 <-> 0, shortest distance
		fDist = 0 - fDist;
	}
	return fDist;		//Returns positive or negative value (Right Or Left)
}

bool SmartTank::m_rotateTowards(Position targetPosition) {
	float fDirection = m_rotationDifference(this->pos, targetPosition);			//Also distance
	
	float fRotationAccuracy = 1.0f;	//Determines when tank will adjust rotation
	//Check if rotation destination has been achieved
	if (fabs(fDirection) < fRotationAccuracy) {
		return true;	//Target rotation achieved
	}
	else {
		//Keep rotating
		if (fDirection > 0) {			//Positive turn right
			this->goRight();
		}
		else if (fDirection < 0) {		//Negative turn left
			this->goLeft();
		}
		return false;
	}
}

bool SmartTank::m_rotateTurretTowards(Position targetPosition) {
	float fDirection = m_rotationDifference(this->pos, this->turretTh, targetPosition);			//Also distance

	float fRotationAccuracy = 1.0f;
	//Check if rotation destination has been achieved
	if (fabs(fDirection) < fRotationAccuracy) {
		return true;	//Target rotation achieved
	}
	else {
		//Keep rotating
		if (fDirection > 0) {			//Positive turn right
			this->turretGoRight();
		}
		else if (fDirection < 0) {		//Negative turn left
			this->turretGoLeft();
		}
		return false;
	}
}

///////////////Setters///////////////////////////
void SmartTank::setDesiredPos(Position newPos) {
	m_DesiredPos = newPos;
}

///////////////Inherited AI TANK FUNCTIONS//////
void SmartTank::reset() {
	m_CurrentState = State::Idle;	//Initial State

	//Movement
	m_bHasDesiredPos = false;
	m_bMoveToPos = false;
	m_bTurretOnTarget = false;
	m_bFastRotation = false;
}

void SmartTank::move() {
	//Decisions made here

	m_Update();

	//States determine how tank will move/not
	if (true) {
		//Reset Movement/Rotation
		this->stop();
		this->stopTurret();
		if (m_bHasDesiredPos) {
			//Rotate Turret
			if (m_bEnemySpotted) {
				if (m_rotateTurretTowards(m_DesiredPos)) {
					m_bTurretOnTarget = true;
				}
				else {
					m_bTurretOnTarget = false;
				}
				//Rotate Tank
				if (m_rotateTowards(m_DesiredPos)) {
					this->goForward();
				}
				m_bEnemySpotted = false;
			}
		}
		else {

		}
	}

	//Reset Flags
		//Movement
	m_bHasDesiredPos = false;
	m_bMoveToPos = false;
	m_bTurretOnTarget = false;

		//Vision
	m_bShellSpotted = false;
	m_bEnemySpotted = false;
	m_bBaseSpotted = false;
	m_bEnemyBaseSpotted = false;
}

void SmartTank::collided() {

}

void SmartTank::markTarget(Position p) {
	//Enemy base spotted
	if (m_vEnemyBasePos.size() <= 0) {
		m_vEnemyBasePos.push_back(p);
		std::cout << "New  Enemy Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
	}
	else {
		if (!findMatch(p, m_vEnemyBasePos)) {
			m_vEnemyBasePos.push_back(p);
			std::cout << "New  Enemy Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
		}
	}
	m_bEnemyBaseSpotted = true;
}

void SmartTank::markEnemy(Position p) {
	//Enemy Tank has been spotted
	m_EnemyPrevPos = m_EnemyCurrPos;	//Store Previous position
	m_EnemyCurrPos = p;						//Store new enemy position
	m_bEnemySpotted = true;
	//std::cout << "Enemy Spotted: x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
}

void SmartTank::markBase(Position p) {
	//Base spotted
	//Loops through bases found and compares the base spotted
	if (m_vBasePos.size() <= 0) {
		m_vBasePos.push_back(p);
		std::cout << "New Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
	}
	else {
		if (!findMatch(p, m_vBasePos)) {		//Iterate through bases spotted and check if they have already been found
			m_vBasePos.push_back(p);
			std::cout << "New Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
		}
	}
	m_bBaseSpotted = true;		//Tank can see base
}

void SmartTank::markShell(Position p) {
	//Projectile Spotted
}

bool SmartTank::isFiring() {
	if (m_bTurretOnTarget) {
		m_bTurretOnTarget = false;
		return false;
	}
	return false;
}

void SmartTank::score(int thisScore, int enemyScore) {
	//Check Scored
}