#include "CheckPatrol.h"

CheckPatrol::CheckPatrol(TankControl *ptr_tank) {
	reposition = new Reposition_Action(ptr_tank);
	addChild(reposition);
}

CheckPatrol::~CheckPatrol() {
	delete reposition;
}

FindBases::FindBases(TankControl* ptr_tank) {

}

FindBases::~FindBases() {

}

BasesNotFound_Condition::BasesNotFound_Condition(TankControl * ptr_tank) {
	this->tank = ptr_tank;
}

Reposition_Action::Reposition_Action(TankControl * ptr_tank) {
	this->tank = ptr_tank;
	fX = 0.0f;
	fY = 0.0f;
	partOfFieldNewDest = 0;
}

bool Reposition_Action::run() {

	if (tank->reachedDesiredPos() || tank->hasCollided()) {			// When tank should reposition
		tank->bIsMoving = false;
		if (tank->hasCollided()) { tank->goBackward(); }
		std::cout << "Reached Position\n";
	}

	if (tank->bEnemySpotted)
	{
		cout << "Stop patrol!" << endl;
		return false;
	}
	if (tank->bEnemyBaseSpotted)
	{
		cout << "Stop patrol!" << endl;

		return false;
	}

	if (!tank->bIsMoving) {						//Reposition tank

		//Find out which part of the field we're in
		if (tank->getX() < tank->middleX) {
			if (tank->getY() < tank->middleY)
				tank->partOfField = 1; // Top Left
			else tank->partOfField = 3; // Bottom Right
		}
		else {
			if (tank->getY() < tank->middleY)
				tank->partOfField = 2; // Top Right
			else
				tank->partOfField = 4; // Bottom Right
		}
		std::cout << tank->partOfField;
		while (!tank->bFoundNewPatrolDestination) {
				fX = (float)(rand() % 600 + 100);		//Generate random position
				fY = (float)(rand() % 400 + 100);

				if (fX < tank->middleX) {
					if (fY < tank->middleY)
						partOfFieldNewDest = 1; // Top Left
					else partOfFieldNewDest = 3; // Bottom Right
				}
				else {
					if (fX < tank->middleY)
						partOfFieldNewDest = 2; // Top Right
					else
						partOfFieldNewDest = 4; // Bottom Right
				}

				if (tank->partOfField == partOfFieldNewDest)
					tank->bFoundNewPatrolDestination = false;
				else
					tank->bFoundNewPatrolDestination = true;
		}
		std::cout << "Repositioning\n";
		tank->bIsMoving = true;					//Tank has is now moving
		tank->bFoundNewPatrolDestination = false;
	}
	tank->patrolTurret();
	tank->setDesiredPosition(fX, fY);
	
	return true;
}

bool BasesNotFound_Condition::run() {
	if (tank->vBasePos.size() >= tank->iNumBases + tank->iNumEnemyBases) {
		//All bases found
		return true;
	}

	return false;
}