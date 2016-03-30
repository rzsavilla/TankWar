#ifndef MOVECONTROL_H
#define MOVECONTROL_H

class MoveControl {
protected:
	bool bHasDesiredPos;	//!< Flag ensuring new position has been set
	bool bMoveToPos;		//!< Tank will move towards desired position
	bool bTurretOnTarget;	//!< Turret is on target/Ready to fire
	bool bFastRotation;		//!< Tank will rotate with the turret
public:
	void resetMoveControl();		//!< Sets all movement flags to false;
};

#endif