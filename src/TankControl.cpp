#include "TankControl.h"

TankControl::TankControl()
{
	bIsDodging = false;

	shellPrevPos = Position(0.0f, 0.0f);
	shellCurrPos = Position(0.0f, 0.0f);
	enemyPrevPos = Position(0.0f, 0.0f);
	enemyCurrPos = Position(0.0f, 0.0f);

	swingingTurretLeft = false;
	swingingTurretRight = false;
}

void TankControl::m_Update() {
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
			bHasTurretDesiredPos = false;
			bFastRotation = false;
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
bool TankControl::m_rotateToAngle(float angle)
{
	float currentOrientation = this->pos.getTh();
	float rotationDiff = angle - currentOrientation;
	if (currentOrientation != angle) // not yet reached
	{
		if (rotationDiff < 0)
		{
			goLeft();
			turretGoLeft();
		}
		else
		{
			goRight();
			turretGoRight();
		}
		return false;
	}
	else // reached
	{
		stopTurret();
		stop();
		return true;
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
	bIsMoving = false;
}

void TankControl::collided() {
	bHasCollided = true;
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
		//std::cout << "Enemy Moving\n";
	}
	else {
		//std::cout << "Enemy Not Moving\n";
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
	if (bShoot && bTurretOnTarget) {			//Ensure tank has aimed before shooting
		bShoot = false;
		return true;					// Tank fires projectile
	}
	return false;
}

void TankControl::score(int thisScore, int enemyScore) {
	//Update scores
	 this->iMyScore= thisScore;
	 this->iEnemyScore = enemyScore;
	//----------Possible to use this as a way to check if shell hits target------------/////////
}

bool TankControl::willShellHit(Position pshell, Position pprevShell)
{
	//get positions of objects
	float pshellX = pshell.getX();
	float pshellY = pshell.getY();

	float pprevShellX = pprevShell.getX();
	float pprevShellY = pprevShell.getY();

	myVector shell(pshellX, pshellY);
	myVector prevShell(pprevShellX, pprevShellY);

	//find corrds of tank bounding box
	myVector topLeft(bb.getX1(), bb.getY1());
	myVector topRight(bb.getX2(), bb.getY1());
	myVector bottomLeft(bb.getX1(), bb.getY2());
	myVector bottomRight(bb.getX2(), bb.getY2());

	bool bShellIsGoingVertical = false;

	float x;
	float y;
	float m;
	float c;

	// find equation of the shell
	// y = mx + c
	// find the gradient
	myVector changeInXY(shell.i() - prevShell.i(), shell.j() - prevShell.j());

	if (changeInXY.i() == 0) // make sure no divide by zero error
	{
		if (shell.i() > topLeft.i() - 10 && shell.i() < topRight.i() + 10) // shell going vcetical
		{
			cout << "vertical" << endl;
			if (shell.j() < topLeft.j())
			{
				return true; // will hit
			}
			if (shell.j() > bottomLeft.j())
			{
				return true; // will hit
			}
			
		}
		return false;
	}
	else
	{
		//find shell gradient
		float shellGradient = changeInXY.j() / changeInXY.i();
		//find y intercept
		float shellC = shell.j() - (shellGradient*shell.i());
		
		// if going horizontal 
		if (shellGradient == 0 && (shell.j() >= topLeft.j() - 10 && shell.j() <= bottomLeft.j()+ 10))
		{
			cout << "horizontal" << endl;
			if (shell.i() < topLeft.i())
			{
				return true; // will hit
			}
			if (shell.i() > topRight.i())
			{
				return true; // will hit
			}
			
		}
		else if (shellGradient == 0)
		{
			return false; // wont hit
		}

		//equation for tank boundry
		float tankC;

		// find lines from each corner of tank and check against shell equation ----------------------------------------
		// use which side it hits to decide how to dodge

		
		//top left to top right
		y = topLeft.j();
		m = shellGradient;
		x = 0;
		c = shellC;
		// find x
		x = (y - c) / m;
		
		if (x >= topLeft.i() - 10 && x <= topRight.i()+10) // if x at this value for y intersects
		{
			return true; // will hit
		}

		//top right to bottom right
		y = 0;
		m = shellGradient;
		x = topRight.i();
		c = shellC;
		// find y
		y = x*m + c;
		if (y >= topRight.j() - 10 && y <= bottomRight.j() + 10) // if y at this value for x intersects
		{
			return true; // will hit

		}

		//bottom right to bottom left
		y = bottomLeft.j();
		m = shellGradient;
		x = 0;
		c = shellC;
		// find x
		x = (y - c) / m;

		if (x >= bottomLeft.i() -10 && x <= bottomRight.i() + 10)
		{
			return true; // will hit

		}


		//bottom left to top left
		y = 0;
		m = shellGradient;
		x = topRight.i();
		c = shellC;
		// find y
		y = x*m + c;
		if (y >= topLeft.j() - 10 && y <= bottomLeft.j() + 10)
		{
			return true; // will hit

		}

	}
	return false; // wont hit
}

void TankControl::evadeShell()
{
	//set up the tank
	float orientation = this->pos.getTh();
	myVector centerOfTank(pos.getX() + 100, pos.getY()+100);
	bIsDodging = true;

	// find angle of shell to the tank

	//make 2 vectors
	float bX = shellCurrPos.getX() - shellPrevPos.getX();
	float bY = shellCurrPos.getY() - shellPrevPos.getY();
	float aX = pos.getX() - oldPos.getX();
	float aY = pos.getY() - oldPos.getY();

	// create vector between the two
	float X = bX - aX;
	float Y = bY - aY;

	float angle = atan(Y / X);
	angle = angle * (180 / 3.14);
	
	float angleDiff;
	float fullDiff;

	float minAngle;
	float maxAngle;

	// convert the angle so it relates to the tanks orientation
	if (angle < 0 && shellCurrPos.getY() <= pos.getY()) angleDiff = 360 + angle;
	else if (angle > 0 && shellCurrPos.getY() <= pos.getY()) angleDiff = 180 + angle;
	else if (angle > 0 && shellCurrPos.getY() > pos.getY()) angleDiff = angle;
	else if (angle < 0 && shellCurrPos.getY() > pos.getY()) angleDiff = 180 + angle;

	//set min and max angle to achieve
	maxAngle = angleDiff + 45;
	minAngle = angleDiff - 45;

	//does the tank need to adjust roation
	// rotation must be +- 45 from the shell
	if (orientation < maxAngle && orientation > minAngle)
	{
		//decide which is closer min or max angle
		if (orientation > angleDiff)
		{
			m_rotateToAngle(maxAngle);
		}
		if (orientation < angleDiff)
		{
			m_rotateToAngle(minAngle);
		}
	}
	else
	{
		//work out which direction is best to drive
		if(orientation < maxAngle-180 && orientation > minAngle-180)
		{
			goForward();
		}
		else
		{
			goBackward();
		}
		
	}

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

bool TankControl::reachedDesiredPos() {
	float fDist = fabs(getDistance(this->pos, this->getDesiredPos()));		// Get Absolute distance

	//std::cout << fDist << std::endl;

	if (fDist < 1.0f) { return true; }	//Tank has reached position
	else { return false;  }				//Tank has not reached reached position

}

//Predictive Aiming
Position TankControl::getEnemyPredictedPos() {
	std::cout << "Aim Predict\n";
	float fShellSpeed = 3.0f;
	float fMoveSpeed = 1.0f;
	//Calculate Enemy Tank velocity
	myVector vel = myVector(this->enemyCurrPos.getX() - this->enemyPrevPos.getY(), this->enemyCurrPos.getY() - this->enemyPrevPos.getY());
	vel = vel.unitVector();
	vel = myVector(vel.i(), vel.j());		//Enemy Tank velocity

	//Position difference between this and enemy tank 
	float fDiffX = this->enemyCurrPos.getX() - this->getX();
	float fDiffY = this->enemyCurrPos.getY() - this->getY();
	float fMagnitude = sqrt(fDiffX * fDiffX + fDiffY * fDiffY);

	//Calculate adjustment angle
	float fAngle;
	fAngle = sin(fDiffX * vel.j() - fDiffY * vel.i() / (fShellSpeed * fMagnitude));
	//Convert angle to vector position/position adjustment
	float x = (cos(fAngle) * (fMagnitude));
	float y = (-sin(fAngle) * (fMagnitude));

	//Add Adjustment position to enemy current position
	Position predictedPos = Position(x + enemyCurrPos.getX(), y + enemyCurrPos.getY());
	//std::cout << "ANGLE: " << fAngle << std::endl;
	std::cout << "Enemy: " << this->enemyCurrPos.getX() << " " << this->enemyPrevPos.getX() << std::endl;
	std::cout << "Predicted: " << predictedPos.getX() << " " << predictedPos.getY() << std::endl;

	return predictedPos;
}

void TankControl::patrolTurret()
{
	// swining the turret 90 degrees each way
	if (swingingTurretLeft == false && swingingTurretRight == false) // if not turning at all
	{
		swingingTurretRight = true;
	}
	if (turretTh >= 90) // finished swinging right so swap to left
	{
		swingingTurretRight = false;
		swingingTurretLeft = true;
	}
	if (turretTh <= 270) // finished swinging left so swap to right
	{
		swingingTurretRight = false;
		swingingTurretLeft = true;
	}


	if (swingingTurretRight == true) // swing it right 
	{
		turretGoRight();
	}

	if (swingingTurretLeft == true) // swing it left 
	{
		turretGoLeft();
	}


}