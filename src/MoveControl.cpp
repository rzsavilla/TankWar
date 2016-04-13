#include "MoveControl.h"

void MoveControl::setDesiredPosition(Position newPos) {
	m_DesiredPos = newPos;
	bHasDesiredPos = true;
	bRotationOnTarget = false;
}
void MoveControl::setDesiredPosition(float x, float y) {
	m_DesiredPos.set(x, y, m_DesiredPos.getTh());
	bHasDesiredPos = true;
	bRotationOnTarget = false;
}
void MoveControl::setTurretDesiredPosition(Position newPos, bool fastRotation) {
	m_DesiredTurretPos = newPos;
	bHasTurretDesiredPos = true;
	bFastRotation = fastRotation; //Tank will move with turret if true
	bTurretRotationOnTarget = false;
}
void MoveControl::setTurretDesiredPosition(float x, float y, bool fastRotation) {
	m_DesiredTurretPos.set(x, y, 0.0f);
	bHasTurretDesiredPos = true;
	bFastRotation = fastRotation; //Tank will move with turret if true
	bTurretRotationOnTarget = false;
}

Position MoveControl::getDesiredPos() { return m_DesiredPos; }
Position MoveControl::getTurretDesiredPos() { return m_DesiredTurretPos; }

bool MoveControl::hasCollided() { return bHasCollided; }

void MoveControl::resetMoveControl() {
	bHasDesiredPos = false;
	//bHasTurretDesiredPos = false;
	//bTurretOnTarget = false;
	//bFastRotation = false;
	bHasCollided = false;
}

