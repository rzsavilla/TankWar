#ifndef VISION_H
#define VISION_H

class Vision {
private:
	const int iNumBases = 6;
	const int iNumEnemyBases = 6;
protected:
	bool bShellSpotted;
	bool bEnemySpotted;
	bool bBaseSpotted;
	bool bEnemyBaseSpotted;
	bool bEnemyMoving;
protected:
	void resetVision();
};

#endif