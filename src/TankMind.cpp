#include "TankMind.h"

TankMind::TankMind() {
	root = new BehaviourTree::Selector;
	checkShell = new CheckShell(this);
	checkEnemy = new CheckEnemy(this);
	checkShoot = new ShootCheck(this);
	createBehaviour();
}

TankMind::~TankMind() {
	delete checkEnemy;
	delete checkShell;
	delete checkShoot;
	delete root;
}

void TankMind::createBehaviour() {
	//root->addChild(checkShell);				//Check for shells first
	//root->addChild(checkEnemy);
	root->addChild(checkShoot);
}

void TankMind::move() {
	//std::cout << "Vision: " << "ETank:" << bEnemySpotted
	//	      << " ETankM:" << bEnemyMoving
	//	      << " Shell:" << bShellSpotted << " Base:"
	//	      << bBaseSpotted << " EBase:" << bEnemyBaseSpotted
	//	      << " OnTarget:" << bTurretOnTarget << std::endl;

	root->run();		//Run

	implementMove();

	//Reset Flags
	resetMoveControl();			//Movement
	resetVision();				//Vision
}

