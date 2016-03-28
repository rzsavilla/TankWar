#include "Calculations.h"

const static float rotationDiff(Position position, Position targetPos) {
	return 0;
}
 const static float rotationDiff(Position pos, Position targetPos, float heading) {
	return 0;
}

bool findMatch(Position pos, std::vector<Position> vPositions) {
	for (int i = 0; i < vPositions.size(); i++) {	//Check if position has already been stored
		if (vPositions.at(i).getX() == pos.getX()) {
			if (vPositions.at(i).getY() == pos.getY()) {
				return true;		//Match found remaining checks/loop ends
			}
		}
	}
	return false;		//No match has been found
}