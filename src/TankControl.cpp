#include "TankControl.h"

TankControl::TankControl()
{
	m_iCallCounter = 0;
	bSideOfImpact.resize(4);
	bSideOfImpact[0] = false;
	bSideOfImpact[1] = false;
	bSideOfImpact[2] = false;
	bSideOfImpact[3] = false;
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

bool TankControl::willShellHit(Position pshell, Position pprevShell)
{
	bSideOfImpact[0] = false; // top
	bSideOfImpact[1] = false; // right
	bSideOfImpact[2] = false; // bottom
	bSideOfImpact[3] = false; // left

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

	// find equation of the shell
	// y = mx + c
	// find the gradient
	myVector changeInXY(shell.i() - prevShell.i(), shell.j() - prevShell.j());

	if (changeInXY.i() == 0) // make sure no divide by zero error
	{
		if (shell.i() > topLeft.i() && shell.i() < topRight.i()) // shell going vcetical
		{
			if (shell.j() < topLeft.j())
			{
				bSideOfImpact[0] = true;
				return true; // will hit
			}
			if (shell.j() > bottomLeft.j())
			{
				bSideOfImpact[2] = true;
				return true; // will hit
			}
			
		}

	}
	else
	{
		float shellGradient = changeInXY.j() / changeInXY.i();
		//find y intercept
		float shellC = shell.j() / (shellGradient*shell.i());
		// shell.j() = shellGradient * shell.i() + shellC
		// general equation y = shellGradient * X + shellC



		// if going horizontal
		if (shellGradient == 0 && (shell.j() >= topLeft.j() && shell.j() <= bottomLeft.j()))
		{
			return true; // will hit
		}
		else if (shellGradient == 0)
		{
			return false; // wont hit
		}

		//equation for tank boundry
		float tankC;

		// find lines from each corner of tank and check against shell equation ----------------------------------------
		// use which side it hides to decide how to dodge

		//top left to top right
		// general equation y = 0 * X + tankC
		tankC = topLeft.j();
		//compare equations
		// y = tankC
		// y = shellGradient * X + shellC
		// X = (y/shellGradient) - shellC
		float x = (tankC / shellGradient) - shellC;
		if (x > topLeft.i() && x < topRight.i())
		{
			bSideOfImpact[0] = true;
			return true; // will hit

		}

		//top right to bottom right
		// general equation x = bottomRight.i()

		//compare equations
		// x = bottomRight.i()
		// y = shellGradient * X + shellC
		// y = shellGradient * bottomRight.i() + shellC
		float y = bottomRight.i() * shellGradient + shellC;
		if (y > topRight.j() && x < bottomRight.j())
		{
			bSideOfImpact[1] = true;
			return true; // will hit

		}

		//bottom right to bottom left
		// general equation y = 0 * X + tankC
		tankC = bottomLeft.j();
		//compare equations
		// y = tankC
		// y = shellGradient * X + shellC
		// X = (y/shellGradient) - shellC
		x = (tankC / shellGradient) - shellC;
		if (x > bottomLeft.i() && x < bottomRight.i())
		{
			bSideOfImpact[2] = true;
			return true; // will hit

		}


		//bottom left to top left
		// general equation x = bottomLeft.i()

		//compare equations
		// x = bottomLeft.i()
		// y = shellGradient * X + shellC
		// y = shellGradient * bottomRight.i() + shellC
		 y = bottomLeft.i() * shellGradient + shellC;
		if (y > topLeft.j() && x < bottomLeft.j())
		{
			bSideOfImpact[3] = true;
			return true; // will hit

		}

	}

	return false; // wont hit
}

void TankControl::evadeShell()
{
	//find the centre of the tank
	float x = pos.getX();
	float y = pos.getY();
	float orientation = this->pos.getTh();
	myVector centreOfTank(x, y);
	myVector despiredPos;

	cout << "top " <<bSideOfImpact[0] << endl;
	cout << "right " << bSideOfImpact[1] << endl;
	cout << "down " << bSideOfImpact[2] << endl;
	cout << "left " << bSideOfImpact[3] << endl;


	if (bSideOfImpact[1] == true) // shell is coming down at tank
	{
		cout << "Go" << endl;
		if ((orientation >= 0 & orientation <= 45)|| orientation < 360 && orientation >315) // dodge to the right
		{
			goForward();
			//cout << "Go" << endl;
			return;
		}
		if ((orientation >= 180 & orientation <= 225) || orientation < 180 && orientation >135) // dodge to the left
		{
			goForward();
			//cout << "Go" << endl;
			return;
		}
	}
	/*
	if (bSideOfImpact[1] == true)// dodge downards
	{
		despiredPos = myVector(centreOfTank.i(), centreOfTank.j() + 300);
		setDesiredPosition(despiredPos.i(), despiredPos.j());
	}
	if (bSideOfImpact[2] == true)// dodge to the left
	{
		despiredPos = myVector(centreOfTank.i() - 300, centreOfTank.j());
		setDesiredPosition(despiredPos.i(), despiredPos.j());
	}
	if (bSideOfImpact[3] == true)// dodge uppwards
	{
		despiredPos = myVector(centreOfTank.i(), centreOfTank.j() - 300);
		setDesiredPosition(despiredPos.i(), despiredPos.j());
	}
	setDesiredPosition(0, 0);
	*/
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