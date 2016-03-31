#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>

#include "position.h"

static float rotationDiff(Position pos1, Position pos2) {
	//Calculate Angle between two points
	float deltaX = pos1.getX() - pos2.getX();
	float deltaY = pos1.getY() - pos2.getY();
	float rad = atan2(deltaY, deltaX);
	float deg = (rad * (180 / PI)) + 180;
	float fDist = (deg - pos1.getTh());;	//Rotation Distance

	//std::cout << "Diff: " << deg << "\t" << "this: " << pos.getTh() << "\t" << "Other:" << deg << "\n";

	if (fabs(fDist) > 180) {		//Ensures full rotation 359 <-> 0, shortest distance
		fDist = 0 - fDist;
	}
	return fDist;		//Returns positive or negative value (Right Or Left)
}

static float rotationDiff(Position pos1, Position pos2, float heading) {
	//Calculate Angle between two points
	float deltaX = pos1.getX() - pos2.getX();
	float deltaY = pos1.getY() - pos2.getY();
	float rad = atan2(deltaY, deltaX);
	float deg = (rad * (180 / PI)) + 180;
	float fDist = (deg - heading);;	//Rotation Distance

	//std::cout << "Diff: " << deg << "\t" << "this: " << pos.getTh() << "\t" << "Other:" << deg << "\n";

	if (fabs(fDist) > 180) {		//Ensures full rotation 359 <-> 0, shortest distance
		fDist = 0 - fDist;
	}
	return fDist;		//Returns positive or negative value (Right Or Left)
}

/*!
	Compare a position with positions within a vector
	returns true if a match is found
*/

static bool findMatch(Position pos, std::vector<Position> vPositions) {
	for (unsigned int i = 0; i < vPositions.size(); i++) {	//Check if position has already been stored
		if (vPositions.at(i).getX() == pos.getX()) {
			if (vPositions.at(i).getY() == pos.getY()) {
				return true;		//Match found remaining checks/loop ends
			}
		}
	}
	return false;		//No match has been found
}

#endif