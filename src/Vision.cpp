#include "Vision.h"

bool Vision::spottedShell() {
	return bShellSpotted;
}
bool Vision::spottedEnemy() {
	return bEnemySpotted;
}
bool Vision::spottedEnemyMoving() {
	return bEnemyMoving;
}
bool Vision::spottedBase() {
	return bBaseSpotted;
}
bool Vision::spottedEnemyBase() {
	return bEnemyBaseSpotted;
}

void Vision::resetVision() {
	bShellSpotted = false;
	bEnemySpotted = false;
	bBaseSpotted = false;
	bEnemyBaseSpotted = false;
	bEnemyMoving = false;
}
