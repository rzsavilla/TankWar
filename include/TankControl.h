/*! \class TankControl
\brief AI Tank implementation FSM
AI for tank using Finite State Machine approach.

	Tank vision, calculations and actions occur here
*/

#ifndef TANKCONTROL_H
#define TANKCONTROL_H

#include <iostream>

#include "aitank.h"				//Base code tank
#include "Vision.h"				//Tank perception data on the world				//Abstraction
#include "MoveControl.h"		//Tank improved move functions/simplified		//Abstraction
#include "Calculations.h"		//Math calculations
#include "myVector.h"			//2D Vector

using namespace std;
using namespace sf;

class TankControl : public  AITank, public MoveControl, public Vision {
private:
	const float fRotationAccuracy = 1.0f;			//!< Offset for rotation, when to end rotation/distance to target rotation
	const float fTurretRotationAccuracy = 1.0f;		//!< Offset for rotation, when to end rotation/distance to target v
	bool swingingTurretLeft;
	bool swingingTurretRight;
public:
	bool bOnTarget;			//!< Tank is rotated towards its desired rotation
	bool bTurretOnTarget;   //!< Turret is rotates towards desired position
public: //Multiple access modifiers to seperate variables and functions (*Easier to read)

	void m_Update();		//!< Update Tank movement and vision.
 
	/*! \brief Rotate tank towards position 
		Changes the tank heading to face target position.
		Returns true when target rotation has been reached.
		\param targetPosition Rotate towards this position
	*/
	bool m_rotateTowards(Position targetPosition);
	bool m_rotateToAngle(float angle);
	bool m_rotateTurretToAngle(float angle);

	/*!	\brief Rotate turret towards posistion
		Turn will aim towards the position. Returns true when rotation is complete
		\param targetPosition Rotate towards this position
	*/
	bool m_rotateTurretTowards(Position targetPosition);

	float getTurretAngle();
public:
	//Note * replace this with Decorator repeat node
	int m_iCallCounter; //!< used for tracking functions that need to be called a certain amount of times

	// some functions of actions that the tank will need to perform
	
	//Note * put this in Calculations class
	bool willShellHit(Position pshell, Position pprevShell);
	bool willShellHitFreindlyBuilding();
	void evadeShell();
	bool checkShellProximity();			//!< check to see if the shell is to close to avoid
	bool reachedDesiredPos();
	void patrolTurret();
	bool spinTank();	

	//Predictive Aiming
	const float kfShellSpeed = 3.0f;	//!< Shell movement speed
	const float kfMoveSpeed = 1.75f;	//!< Tank movement speed
	/*!
		Calculate and return predicted enemy position
		Code and resource used for function found:
		https://www.scirra.com/forum/what-is-the-formula-for-predictive-aim_t115697
		https://www.reddit.com/r/gamedev/comments/16ceki/turret_aiming_formula/c7vbu2j
	*/
	Position getEnemyPredictedPos(); 
public:
	TankControl();	//!< Default Contructor

public:
	//////////////////Virtual functions inherited from AI tank are defined by this class///////////////

	void reset();		//!< Reset any variables you need to whent he tank has been shot

	void collided();	//!< Called by the game object when the tank has collided

	/*! Called by the game object when a target (enemy building) comes within the tanks visible range
		\param Position of the acquired target
	*/
	void markEnemy(Position p);

	/*! Called by the game object when the enemy tank comes within the tanks visible range
		\param Position of the enemy tank
	*/
	void markTarget(Position p);

	/*! Called by the game object when one of you own buildings comes within the tanks visible range
		\param Position of the home building
	*/
	void markBase(Position p);

	/*!< Called by the game object when enemy shell comes within the tanks visible range
		\param Position of an enemy shell
	*/
	void markShell(Position p);

	bool isFiring();								//!< Called by the game object each frame.  When this function returns true (and ammo is availbe and loaded) the tank will fire a shell

	void score(int thisScore, int enemyScore);		//!< Notifies tank of current Score
};

#endif