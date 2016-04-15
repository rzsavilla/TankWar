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
	for (std::vector<Position>::iterator it = vPositions.begin(); it < vPositions.end(); it++) {	//Check if position has already been stored
		if (it->getX() == pos.getX()) {
			if (it->getY() == pos.getY()) {
				return true;		//Match found remaining checks/loop ends
			}
		}
	}
	return false;		//No match has been found
}

/*!
	Return the distance between two positions
*/
static float getDistance(const Position &pos1, const Position &pos2) {
	//std::cout << "Distance: " << fDist << std::endl;
	return (float)sqrt((pow((float)(pos2.getX() - pos1.getX()), 2.0)) + 
					   (pow((float)(pos2.getY() - pos1.getY()), 2.0)));
} 

/*!
	Return the distance between two positions
*/
static float getDistance(float x1, float y1, float x2, float y2) {
	return (float)sqrt((pow((x2 - x1), 2.0)) + (pow((y2 - y1), 2.0)));
}

/*!
	Compute Distance approximation (Taxicab/Manhattan)
	Formula from
	https://en.wikibooks.org/wiki/Algorithms/Distance_approximations
*/
static float approxDist(const Position& pos1, const Position &pos2) {
	return pow(pos1.getX() + pos2.getX(), 2) + pow(pos1.getY() - pos1.getY(), 2);
}

static float approxDist(float x1, float y1, float x2, float y2) {
	Position pos1(x1, y1);
	Position pos2(x2, y2);
	return approxDist(pos1, pos2);
}

#endif