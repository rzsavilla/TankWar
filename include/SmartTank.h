/*! \class SmartTank
\brief AI Tank implementation FSM
AI for tank using Finite State Machine approach.

	Tank vision, calculations and actions occur here
*/

#ifndef SMARTTANK_H
#define SMARTTANK_H

#include "aitank.h"
#include "Vision.h"
#include "MoveControl.h"
#include "Calculations.h"

enum class State { Idle, Evade, Patrol, Attack }; //Tank State

class SmartTank : public  AITank, public MoveControl, public Vision {
protected:
	State m_CurrentState;			//!< Current Tank State
	Position m_DesiredPos;			//!< Tank will move to this position
	Position m_DesiredTurretPos;	//!< Turret will rotate towards this

	bool m_bHasDesiredPos;			//!< Flag ensuring new position has been set
	bool m_bMoveToPos;				//!< Tank will move towards desired position
	bool m_bTurretOnTarget;			//!< Turret is on target/Ready to fire
	bool m_bFastRotation;			//!< Tank will rotate with the turret

	//Vision What the Tank can see
	bool m_bShellSpotted;			//!< Can see a shell
	bool m_bEnemySpotted;			//!< Can see the enemy tank
	bool m_bBaseSpotted;			//!< Can see at least 1 base
	bool m_bEnemyBaseSpotted;		//!< Can see at least 1 enemy base
	bool m_bEnemyMoving;			//!< Can see that the enemy is moving

	Position m_ShellPrevPos;		//!< Previous position of shell
	Position m_ShellCurrPos;		//!< Current position of shell
	Position m_EnemyPrevPos;		//!< Previous position of enemy tank
	Position m_EnemyCurrPos;		//!< Latest position of enemy tank
	std::vector<Position> m_vBasePos;		//!< Positions of spotted bases
	std::vector<Position> m_vEnemyBasePos;	//!< Positions of spotted enemy bases

protected: //double access modifiers to seperate variables and functions (*Easier to read)
	//State Actions
	void m_Idle();			//!< Actions when Idle
	void m_Patrol();		//!< Actions when patrolling
	void m_Evade();			//!< Action when evading
	void m_Attack();		//!< Actions when attacking

	void m_resetMovement(); //!< Sets all movement flags to false;
	void m_resetVision();	//!< Sets all vision flags to false;
	void m_Update();		//!< 

	void m_ChangeState(State newState);
 
	//Calculations/Actions
		//These functions will be moved to another class
	float m_rotationDifference(Position pos, Position targetPos);	//!< Returns angle difference/distance between this position and other position
	float m_rotationDifference(Position pos, float heading, Position targetPos);

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

	void setDesiredPos(Position newPos);	//!< Tank will move towards set Position \param newPos Target Position
protected:

public:
	SmartTank();					//!< Default Contructor

public:
	//////////////////Virtual functions inherited from AI tank///////////////////////////
	void reset();		//!< Reset any variables you need to whent he tank has been shot
	void move();		//!< Move the tank
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
};

#endif