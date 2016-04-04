/*! \class TankControl
\brief AI Tank implementation FSM
AI for tank using Finite State Machine approach.

	Tank vision, calculations and actions occur here
*/

#ifndef TANKCONTROL_H
#define TANKCONTROL_H

#include <iostream>

#include "aitank.h"
#include "Vision.h"
#include "MoveControl.h"
#include "Calculations.h"
#include "myVector.h"

using namespace std;
using namespace sf;

class TankControl : public  AITank, public MoveControl, public Vision {
private:
	const float fRotationAccuracy = 5.0f;
	const float fTurretRotationAccuracy = 5.0f;
protected:
	bool bOnTarget;			//!< Tank is rotated towards its desired rotation
	bool bTurretOnTarget;   //!< Turret is rotates towards desired position
public: //Multiple access modifiers to seperate variables and functions (*Easier to read)
	//State Actions

	void m_Update();		//!< Update Tank movement and vision.
 
	/*! \brief Rotate tank towards position 
		Changes the tank heading to face target position.
		Returns true when target rotation has been reached.
		\param targetPosition Rotate towards this position
	*/
	bool m_rotateTowards(Position targetPosition);

	/*!	\brief Rotate turret towards posistion
		Turn will aim towards the position. Returns true when rotation is complete
		\param targetPosition Rotate towards this position
	*/
	bool m_rotateTurretTowards(Position targetPosition);

public:
	//Note * replace this with Decorator repeat node
	int m_iCallCounter; //!< used for tracking functions that need to be called a certain amount of times

	// some functions of actions that the tank will need to perform
	
	//Note * put this in Calculations class
	bool willShellHit(Position ptank, Position pshell, Position pprevShell);
	bool checkShellProximity(); //!< check to see if the shell is to close to avoid
	bool isMoving = false;; //!< Flag set when tank is moving

public:
	TankControl();					//!< Default Contructor

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

	bool isFiring(); //!< Called by the game object each frame.  When this function returns true (and ammo is availbe and loaded) the tank will fire a shell

	void score(int thisScore, int enemyScore);		//!< Notifies tank of current Score

	void decisionTree(); //!< called to updated the action the tank should be taking
};

#endif