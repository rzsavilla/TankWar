#include "TankMind.h"

TankMind::TankMind() {
	createBehaviour();
	
}

TankMind::~TankMind() {
	delete checkShell;
	delete checkEnemy;
	delete checkEnemyBase;
	delete checkPatrol;
	delete root;
}

void TankMind::createBehaviour() {
	root->addChild(checkShell);
	root->addChild(checkEnemy);
	root->addChild(checkEnemyBase);
	root->addChild(checkPatrol);
}

void TankMind::move() {
	/*
	//Print what the tank can see
	std::cout << "Vision: " << "ETank:" << bEnemySpotted
		      << " ETankM:" << bEnemyMoving
		      << " Shell:" << bShellSpotted << " Base:"
		      << bBaseSpotted << " EBase:" << bEnemyBaseSpotted
		      << " OnTarget:" << bTurretOnTarget << std::endl;
	*/
	//Reset tank rotation
	this->stop();			//Stop tank rotation 
	this->stopTurret();		//Stop turret rotation

	root->run();			// run through the behaviour tree

	m_Update();
	//implementMove();
}