#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>

#include "position.h"

/*!
	
*/
const static float rotationDiff(Position position, Position targetPos);
const static float rotationDiff(Position pos, Position targetPos, float heading);

/*!
	Compare a position with positions within a vector
	returns true if a match is found
*/

bool findMatch(Position pos, std::vector<Position> vPositions);

#endif