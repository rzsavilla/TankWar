#ifndef MOVECONTROL_H
#define MOVECONTROL_H

#include "position.h"

class MoveControl {
protected:
	bool bHasDesiredPos;		//!< Tank will move towards desired position
	bool bHasTurretDesiredPos;  //!< Turret will rotate towards desired position
	bool bTurretOnTarget;		//!< Turret is on target/Ready to fire
	bool bFastRotation;			//!< Tank will rotate with the turret
	
private:
	Position m_DesiredPos;			//!< Tank will move to this position
	Position m_DesiredTurretPos;	//!< Turret will rotate towards this
public:
	bool bHasCollided;
	bool bRotationOnTarget;			//Tank has rotated towards desired position
	bool bTurretRotationOnTarget;	//Turret has rotates towards desired position

	bool hasCollided();				//!< Check if tank has collided

	void setDesiredPosition(Position newPos);		 //!< Will set a position
	void setDesiredPosition(float x, float y);		 //!< Will set a position
	void setTurretDesiredPosition(Position newPos, bool fastRotation = false);  //!< Will set position for turret to rotate towards
	void setTurretDesiredPosition(float x, float y, bool fastRotation = false); //!< Will set position for turret to rotate towards

	Position getDesiredPos();
	Position getTurretDesiredPos();

	void resetMoveControl();		 //!< Sets all movement flags to false;
};

#endif