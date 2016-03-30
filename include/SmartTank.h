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
#include "myVector.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum class State { Idle, Evade, Patrol, Attack }; //Tank State

class SmartTank : public  AITank, public MoveControl, public Vision {
protected:
	State m_CurrentState;			//!< Current Tank State
	Position m_DesiredPos;			//!< Tank will move to this position
	Position m_DesiredTurretPos;	//!< Turret will rotate towards this

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

	string sCurrentState;					//!< String for the position in the decision tree
	void setCurrentState(string nextState); //!< change the position in the tree
	

private:
	int m_iCallCounter; //!< used for tracking functions that need to be called a certain amount of times

	// some functions of actions that the tank will need to perform
	void spinTankAndTurret();  //!< spin tank and turret by 1 degree to the right
	bool willShellHit(Position ptank, Position pshell, Position pprevShell);
	bool checkShellProximity(); //!< check to see if the shell is to close to avoid

protected:

public:
	SmartTank();					//!< Default Contructor

public:
	//////////////////Virtual functions inherited from AI tank are defined by this class///////////////
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

	void decisionTree(); //!< called to updated the action the tank should be taking
};

#endif