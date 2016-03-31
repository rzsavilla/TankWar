#include "SmartTank.h"

SmartTank::SmartTank()
{
	sCurrentState = "Idle";
	m_iCallCounter = 0;
}

void SmartTank::m_Update() {

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
/*
void SmartTank::move() {
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
*/
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

void SmartTank::decisionTree()
{
	if(sCurrentState == "Idle")
	{
		
		setCurrentState("Scan for shells");
		return;
	}

	if(sCurrentState == "Scan for shells")
	{
		
		//call scan for shells
		if(m_iCallCounter < 360/1.75f) // full circle divided by the speed of tank
		{
			//spin the tank and turret
			spinTankAndTurret();
			//check if its seen a shell
			if(bShellSpotted)
			{
				setCurrentState("Can avoid?");
				this->stop();
				this->stopTurret();
				m_iCallCounter = 0;
				return;
			}
			
			m_iCallCounter++;
			return;
		}
		setCurrentState("Scan for enemies");
		this->stop();
		this->stopTurret();
		m_iCallCounter = 0;
		return;
	}

	if(sCurrentState == "Can avoid?")
	{
		// will it hit
		if(willShellHit(pos,shellCurrPos,shellPrevPos));
		{
			//call shellProximity
			if(checkShellProximity())
			{
				//dodje shell
				cout << " dodje shell " << endl;
				setCurrentState("Avoid");
				return;
			}
			//shell will hit , attempt to find a target
			cout << " shell will hit , attempt to find a target " << endl;
			setCurrentState("Scan for enemies");
			return;
			
		}
		//it wil miss so begin trace of shell
		cout << " //it wil miss so begin trace of shell " << endl;
		setCurrentState("Trace shell");
		return;
	}

	if(sCurrentState == "Scan for enemies")
	{
		//call scan for enemies
		
		return;
	}

	if(sCurrentState == "Avoid")
	{
		//call avoid
		setCurrentState("Trace shell");
		return;
	}

	

}

void SmartTank::setCurrentState(string nextState)
{
	sCurrentState = nextState;
}

void SmartTank::spinTankAndTurret()
{
	turretGoRight();
	goRight();

}

bool SmartTank::willShellHit(Position ptank, Position pshell, Position pprevShell)
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

bool SmartTank::checkShellProximity()
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