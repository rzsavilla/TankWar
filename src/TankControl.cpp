#include "TankControl.h"

TankControl::TankControl()
{
	m_iCallCounter = 0;
}

void TankControl::m_Update() {
	//Movement
	stop();
	stopTurret();

	if (bHasTurretDesiredPos) {
		if (!m_rotateTurretTowards(getTurretDesiredPos())) {
			//Target rotation not yet achieved;
			if (bFastRotation) {
				//Tank Rotates with turret
				if (rotationDiff(this->pos, getTurretDesiredPos(), this->turretTh) > 0) {
					goRight();
				}
				else {
					goLeft();
				}
			}
			bTurretOnTarget = false;
		}
		else {
			bTurretOnTarget = true;
		}
	}

	if (bHasDesiredPos && bFastRotation == false) {
		if (m_rotateTowards(getDesiredPos())) { //Rotate towards position
			goForward(); //Towards position
		}
		else {
			bOnTarget = true;
		}
	}

	//Reset Flags
	resetMoveControl();
	resetVision();
}

bool TankControl::m_rotateTowards(Position targetPosition) {
	float fDirection = rotationDiff(this->pos, targetPosition);			//Also distance
	
	//Check if rotation destination has been achieved
	if (fabs(fDirection) < fRotationAccuracy) {
		//Stop Tank rotation
		stop();
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

bool TankControl::m_rotateTurretTowards(Position targetPosition) {
	float fDirection = rotationDiff(this->pos, targetPosition,this->turretTh);			//Also distance

	//Check if rotation destination has been achieved
	if (fabs(fDirection) < fTurretRotationAccuracy) {
		//Stop turret rotation
		stopTurret();
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

///////////////Inherited AI TANK FUNCTIONS//////
void TankControl::reset() {
	resetVision();
	resetMoveControl();
	isMoving = false;
}

void TankControl::collided() {

}

void TankControl::markTarget(Position p) {
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
	//bEnemyBaseSpotted = true;		//Enemy can see an enemy base
}

void TankControl::markEnemy(Position p) {
	//Enemy Tank has been spotted
	enemyPrevPos = enemyCurrPos;	//Store Previous position
	enemyCurrPos = p;				//Store new enemy position
	if (enemyPrevPos.getX() != enemyCurrPos.getX()
		&& enemyPrevPos.getY() != enemyCurrPos.getY()) {
		bEnemyMoving = true;
	}
	else {
		bEnemyMoving = false;
	}
	bEnemySpotted = true;
	//std::cout << "Enemy Spotted: x:" << (int)p.getX() << " y:" << (int)p.getY() << std::endl;
}

void TankControl::markBase(Position p) {
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
	//bBaseSpotted = true;		//Tank can see base
}

void TankControl::markShell(Position p) {
	//Projectile Spotted

	//------How should it store positions of shells when it spots multiple shells-----///////
	this->bShellSpotted = true;

	this->shellPrevPos = shellCurrPos;
	this->shellCurrPos = p;
	//std::cout << "Projectile Spotted: x" << p.getX() << " y:"<< p.getY() << std::endl;
}

bool TankControl::isFiring() {
	if (bTurretOnTarget) {
		bTurretOnTarget = false;
		return true;					// Tank fires projectile
	}
	return false;
}

void TankControl::score(int thisScore, int enemyScore) {
	//Check Scored

	//----------Possible to use this as a way to check if shell hits target------------/////////
}

bool TankControl::willShellHit(Position ptank, Position pshell, Position pprevShell)
{
	float tankX = ptank.getX();
	float tankY = ptank.getY();

	float pshellX = pshell.getX();
	float pshellY = pshell.getY();

	float pprevShellX = pprevShell.getX();
	float pprevShellY = pprevShell.getY();

	myVector tank(tankX,tankY);
	myVector shell(pshellX,pshellY);
	myVector prevShell(pprevShellX,pprevShellY);

	//find the distance from the shell to the tank
	myVector dist = shell.subtract(tank);

	//find the path of the shell
	myVector shellPath = shell.subtract(prevShell);

	// find how long it will take the shell to reach the tank
	float time = dist.magnitude(dist)/3;

	//move the shell to where it would be at that time 
	shellPath = myVector(shell.i()*time,shell.j()*time);

	//check wheather the shell is colliding a this new position
	FloatRect shellRect(shellPath.i(),shellPath.j(),6.0f,12.0f);
	FloatRect tankRect(tank.i(),tank.j(),200.0f,200.0f);

	if(shellRect.intersects(tankRect))
	{
		return true; // will hit
	}
	return false; // wont hit
}

bool TankControl::checkShellProximity()
{
	float tankX = getX();
	float tankY = getY();

	float pshellX = shellCurrPos.getX();
	float pshellY = shellCurrPos.getY();

	myVector vectorDistance(tankX - pshellX, tankY - pshellY);
	float distance = vectorDistance.magnitude(vectorDistance);

	if(distance >= 66)
	{
		return true; // wont hit
	}
	return false; // will hit
}

bool TankControl::tankReachedDestination(float dx, float dy) {
	float tankX = getX();
	float tankY = getY();

	if ((tankX > dx && tankX < dx + 200.f) && (tankY > dy && tankY < dy + 200.f))
	return true;
	else return false;
}