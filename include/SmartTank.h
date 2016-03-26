/*! \class SmartTank
\brief AI Tank implementation FSM
AI for tank using Finite State Machine approach.
*/

#ifndef SMARTTANK_H
#define SMARTTANK_H

#include "aitank.h"

enum class State { Idle, Evade, Patrol, Attack }; //Tank State

class SmartTank : public  AITank{
private:
	State m_CurrentState;	//!< Current Tank State
	Position m_DesiredPos;	//!< Tank will move to this position
	bool m_bHasDesiredPos;	//!< Flag ensuring new position has been set
	bool m_bMoveToPos;		//!< Tank will move towards desired position
	bool m_bRotate;
	bool m_bTurretOnTarget;

private: //double access modifiers to seperate varibales and functions (*Easier to read)
	//State Actions
	void m_Idle();			//! Actions when Idle
	void m_Patrol();		//!< Actions when patrolling
	void m_Evade();			//!< Action when evading
	void m_Attack();		//!< Actions when attacking

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