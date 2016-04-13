#ifndef MOVECONTROL_H
#define MOVECONTROL_H

#include "position.h"
#include "Calculations.h"

class MoveControl {
public:
	bool bHasDesiredPos;		//!< Tank will move towards desired position
	bool bHasTurretDesiredPos;  //!< Turret will rotate towards desired position
	bool bTurretOnTarget;		//!< Turret is on target/Ready to fire
	bool bFastRotation;			//!< Tank will rotate with the turret
	bool bHasCollided;			//!< Tank has collided with an object

	Position m_DesiredPos;			//!< Tank will move to this position
	Position m_DesiredTurretPos;	//!< Turret will rotate towards this
public:
	bool bRotationOnTarget;			//Tank has rotated towards desired position
	bool bTurretRotationOnTarget;	//Turret has rotates towards desired position

	bool bIsDodging;				//!< Tank is currently attempting to dodge bullet
	bool bIsMoving;					//!< Tank currently has a position to move towards

	//Do not forget to reset bShoot after shooting
	bool bShoot;					//!< Tank will shoot if this is true 
public:
	void setDesiredPosition(Position newPos);		 //!< Will set a position
	void setDesiredPosition(float x, float y);		 //!< Will set a position
	void setTurretDesiredPosition(Position newPos, bool fastRotation = false);  //!< Will set position for turret to rotate towards
	void setTurretDesiredPosition(float x, float y, bool fastRotation = false); //!< Will set position for turret to rotate towards

	bool hasCollided();				//!< Returns bHasCollided

	Position getDesiredPos();		//!< Return tanks target position
	Position getTurretDesiredPos();	//!< Return turrets target position to rotate towards

	void resetMoveControl();		//!< Sets all movement flags to false;
};

#endif