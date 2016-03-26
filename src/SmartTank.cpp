#include "SmartTank.h"

SmartTank::SmartTank() {
	m_CurrentState = State::Idle;
	m_bRotate = true;
	m_bMoveToPos = false;
	m_bHasDesiredPos = false;
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
	
	float fRotationAccuracy = 1.0f;
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
	m_DesiredPos = pos;				//Desired Position is current Position

	//Flags
	m_bHasDesiredPos = false;		//Stop movement
	m_bMoveToPos = false;
}

void SmartTank::move() {
	//Decisions made here

		//States determine how tank will move/not
	switch (m_CurrentState)
	{
	case State::Idle:

		break;
	case State::Evade:

		break;
	case State::Patrol:

		break;
	case State::Attack:

		break;
	default:
		break;
	}

	if (true) {
		if (m_bHasDesiredPos) {
			//Rotate Turret
			if (m_rotateTurretTowards(m_DesiredPos)) {
				m_bTurretOnTarget = true;
				this->stop();
			}
			//Rotate Tank
			if (m_rotateTowards(m_DesiredPos)) {
				this->stop();
				this->goForward();
			}
		}
		else {

		}
	}
}

void SmartTank::collided() {

}

void SmartTank::markTarget(Position p) {
	//Enemy base spotted
}

void SmartTank::markEnemy(Position p) {
	//Enemy Target has been spotted
		//Change State?
	m_DesiredPos = p;
	m_bHasDesiredPos = true;
}

void SmartTank::markBase(Position p) {
	//Base spotted
}

void SmartTank::markShell(Position p) {
	//Projectile Spotted
}

bool SmartTank::isFiring() {
	if (m_bTurretOnTarget) {
		m_bTurretOnTarget = false;
		return true;
	}
	return false;
}

void SmartTank::score(int thisScore, int enemyScore) {
	//Check Scored
}