/*
	Data for what the tank can see.
*/

#ifndef VISION_H
#define VISION_H

#include <vector>
#include "position.h"

class Vision {
public:
	//What the tank can see
	bool bShellSpotted;			//!< Can see a shell
	bool bEnemySpotted;			//!< Can see the enemy tank
	bool bBaseSpotted;			//!< Can see at least 1 base
	bool bEnemyBaseSpotted;		//!< Can see at least 1 enemy base
	bool bEnemyMoving;			//!< Can see that the enemy is moving
public:
	static const int iNumBases = 6;				//!< Max number of Bases, Used to determine when all bases found
	static const int iNumEnemyBases = 6;		//!< Max number of Enemy Bases, Used to determine when all bases found 
public:
	int iMyScore;							//!< Stores current score
	int iEnemyScore;						//!< Stores enemy score
	Position shellPrevPos;					//!< Previous position of shell
	Position shellCurrPos;					//!< Current position of shell
	Position enemyPrevPos;					//!< Previous position of enemy tank
	Position enemyCurrPos;					//!< Latest position of enemy tank
	Position enemyBasePos;					//!< Position of last enemy base spotted
	std::vector<std::pair<bool, Position>>::iterator it;
	std::vector<Position> vBasePos;			//!< Positions of spotted bases
	std::vector<Position> vEnemyBasePos;	//!< Positions of spotted enemy bases

	bool hasPredictedEnemyPos;				//!< Flag for when predicted enemy position is available
	Position predictedEnemyPos;				//!< Stores possible position of enemy tank, calculated based on previous position and heading of enemy tank
public:
	bool spottedShell();
	bool spottedEnemy();
	bool spottedEnemyMoving();
	bool spottedBase();
	bool spottedEnemyBase();

	void resetVision();			//!< Set all boolean variables to false
};

#endif