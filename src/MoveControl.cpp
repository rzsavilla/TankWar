#include "MoveControl.h"

void MoveControl::resetMoveControl() {
	bHasDesiredPos = false;
	bMoveToPos = false;
	bFastRotation = false;
}