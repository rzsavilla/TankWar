#include "TankMind.h"

TankMind::TankMind() {
	root = new BehaviourTree::Selector;
	checkShell = new CheckShell(this);
	checkEnemy = new CheckEnemy(this);
	
	createBehaviour();
}

TankMind::~TankMind() {
	delete checkEnemy;
	delete checkShell;
	delete root;
}

void TankMind::createBehaviour() {
	root->addChild(checkShell);				//Check for shells first
	root->addChild(checkEnemy);
}

void TankMind::move() {
	//std::cout << "Vision: " << "ETank:" << bEnemySpotted
	//	      << " ETankM:" << bEnemyMoving
	//	      << " Shell:" << bShellSpotted << " Base:"
	//	      << bBaseSpotted << " EBase:" << bEnemyBaseSpotted
	//	      << " OnTarget:" << bTurretOnTarget << std::endl;

	root->run();		//Run

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

	//Reset Flags
	resetMoveControl();			//Movement
	resetVision();				//Vision
}

