#include "PlayerTank.h"
#include <iostream>
PlayerTank::PlayerTank() // Construtor
{
	clearMovement();
	turretLeft = false;
	turretRight = false;
	numberOfShells = 15;

	bodyTex.loadFromFile("assets\\blueTank.png");
	body.setTexture(bodyTex);
	body.setOrigin(100,100);
	body.setScale(0.2f,0.2f);

	turretTex.loadFromFile("assets\\blueTankTurret.png");
	turret.setTexture(turretTex);
	turret.setOrigin(46,44);
	turret.setScale(0.2f,0.2f);
}

void PlayerTank::move()
{	
	implementMove();
}

void PlayerTank::fire()
{
	
}
void PlayerTank::decisionTree()
{
	if(sCurrentState == "Idle")
	{
		setCurrentState("Scan for shells");
		return;
	}
	if(sCurrentState == "Scan for shells");
	{
		//call scan for shells
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Can avoid?");
	{
		//call shellProximity
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Scan for enemies");
	{
		//call scan for enemies
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Avoid");
	{
		//call avoid
		setCurrentState("Trace shell");
		return;
	}

	if(sCurrentState == "Trace shell");
	{
		//call trace shell
		setCurrentState("Shoot player player");
		return;
	}

	if(sCurrentState == "Shoot player player");
	{
		//call Shoot player player
		setCurrentState("Hit player ?");
		return;
	}

	if(sCurrentState == "Hit player?");
	{
		//call hit detection
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Move");
	{
		//call move
		setCurrentState("Scan for buildings");
		return;
	}

	if(sCurrentState == "Scan for buildings");
	{
		//call scan for buildings
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Building counter");
	{
		//counter++
		setCurrentState("Building check");
		return;
	}

	if(sCurrentState == "Building check");
	{
		//if counter > num.shells
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Shoot building");
	{
		//call shoot building
		setCurrentState("Hit building ?");
		return;
	}

	if(sCurrentState == "Hit building ?");
	{
		//call hit for buildings
		makeDecision(true);
		return;
	}

	if(sCurrentState == "Patrol");
	{
		//call Patrol for buildings
		setCurrentState("Found building ?");
		return;
	}

	if(sCurrentState == "Found building ?");
	{
		//call found building
		makeDecision(true);
		return;
	}
	
	
	

}

void PlayerTank::setCurrentState(string nextState)
{
	sCurrentState = nextState;
}

void PlayerTank::makeDecision(bool decision)
{
	if(sCurrentState == "Scan for shells");
	{
		if(decision == true)
		{
			setCurrentState("Can avoid?");
			return;
		}
		else
		{
			setCurrentState("Scan for enemies");
			return;
		}
	}
	if(sCurrentState == "Can avoid?");
	{
		if(decision == true)
		{
			setCurrentState("Avoid");
			return;
		}
		else
		{
			setCurrentState("Scan for enemies");
			return;
		}
	}

	if(sCurrentState == "Hit player ?");
	{
		if(decision == true)
		{
			setCurrentState("Move");
			return;
		}
		else
		{
			setCurrentState("Idle");
			return;
		}
	}

	if(sCurrentState == "Scan for enemies");
	{
		if(decision == true)
		{
			setCurrentState("Shoot player player");
			return;
		}
		else
		{
			setCurrentState("Scan for buildings");
			return;
		}
	}

	if(sCurrentState == "Scan for buildings");
	{
		if(decision == true)
		{
			setCurrentState("Shoot buidling");
			return;
		}
		else
		{
			setCurrentState("Building counter");
			return;
		}
	}

	if(sCurrentState == "Building check");
	{
		if(decision == true)
		{
			setCurrentState("Patrol for buildings");
			return;
		}
		else
		{
			setCurrentState("Idle");
			return;
		}
	}

	if(sCurrentState == "Hit building ?");
	{
		if(decision == true)
		{
			setCurrentState("Idle");
			return;
		}
		else
		{
			setCurrentState("Move");
			return;
		}
	}

	if(sCurrentState == "Found building ?");
	{
		if(decision == true)
		{
			setCurrentState("Idle");
			return;
		}
		else
		{
			setCurrentState("Patrol");
			return;
		}
	}

	
	
}