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
	if (bShellSpotted) {
		//Check if oncoming
			//Evade
		//else ignore

		//Trace bullet
			//Set predicted enemy pos
	}

	if (bEnemySpotted) {
		//Calculate enemy heading
		m_DesiredPos = enemyCurrPos;
		bHasDesiredPos = true;
		//Track enemy 
			//Fast rotate towards enemy
	}

	if (bBaseSpotted) {

	}

	if (bEnemyBaseSpotted) {

	}
}

bool SmartTank::m_rotateTowards(Position targetPosition) {
	float fDirection = rotationDiff(this->pos, targetPosition);			//Also distance
	
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
	float fDirection = rotationDiff(this->pos, targetPosition,this->turretTh);			//Also distance

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

	resetVision();
	resetMoveControl();
}

void SmartTank::move() {
	//Decisions made here
	m_Update();

	//Print tank vision
	std::cout << "Vision: " << "ETank:" << bEnemySpotted << " ETankM:" << bEnemyMoving 
			  << " Shell:" << bShellSpotted << " Base:" << bBaseSpotted << " EBase:" << bEnemyBaseSpotted 
			  << " OnTarget:" << bTurretOnTarget << std::endl;

	//States determine how tank will move/not
	if (true) {
		//Reset Movement/Rotation
		this->stop();
		this->stopTurret();
		if (bHasDesiredPos) {
			//Rotate Turret
			if (bEnemySpotted) {
				if (m_rotateTurretTowards(m_DesiredPos)) {
					bTurretOnTarget = true;
				}
				else {
					bTurretOnTarget = false;
				}
				//Rotate Tank
				if (m_rotateTowards(m_DesiredPos)) {
					this->goForward();
				}
				bEnemySpotted = false;
			}
		}
		else {

		}
	}

	//Reset Flags
	resetMoveControl();			//Movement
	resetVision();				//Vision
}

void SmartTank::collided() {

}

void SmartTank::markTarget(Position p) {
	//Enemy base spotted
	if (vEnemyBasePos.size() <= 0) {
		vEnemyBasePos.push_back(p);
		std::cout << "New  Enemy Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
	}
	else {
		if (!findMatch(p, vEnemyBasePos)) {
			vEnemyBasePos.push_back(p);
			std::cout << "New  Enemy Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
		}
	}
	bEnemyBaseSpotted = true;		//Enemy can see an enemy base
}

void SmartTank::markEnemy(Position p) {
	//Enemy Tank has been spotted
	enemyPrevPos = enemyCurrPos;	//Store Previous position
	enemyCurrPos = p;				//Store new enemy position
	bEnemySpotted = true;
	//std::cout << "Enemy Spotted: x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
}

void SmartTank::markBase(Position p) {
	//Base spotted
	//Loops through bases found and compares the base spotted
	if (vBasePos.size() <= 0) {
		vBasePos.push_back(p);
		//std::cout << "New Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
	}
	else {
		if (!findMatch(p, vBasePos)) {		//Iterate through bases spotted and check if they have already been found
			vBasePos.push_back(p);
			//std::cout << "New Building:" << " x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
		}
	}
	bBaseSpotted = true;		//Tank can see base
}

void SmartTank::markShell(Position p) {
	//Projectile Spotted

	//------How should it store positions of shells when it spots multiple shells-----///////

	//std::cout << "Projectile Spotted: x" << p.getX() << " y:"<< p.getY() << std::endl;
	bShellSpotted = true;
}

bool SmartTank::isFiring() {
	if (bTurretOnTarget) {
		bTurretOnTarget = false;
		return true;					// Tank fires projectile
	}
	return false;
}

void SmartTank::score(int thisScore, int enemyScore) {
	//Check Scored

	//----------Possible to use this as a way to check if shell hits target------------/////////
}