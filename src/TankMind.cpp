#include "TankMind.h"

TankMind::TankMind() {
	createBehaviour();
	bIsDodging = false;
}

TankMind::~TankMind() {
	delete checkShell;
	delete checkEnemy;
	delete root;
}

void TankMind::createBehaviour() {
	root->addChild(checkShell);
	//root->addChild(checkEnemy);
	//root->addChild(checkEnemyBase);
	//root->addChild(checkPatrol);
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

	if (root->run()) {

	}

	m_Update();
}