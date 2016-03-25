#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include "tank.h"
#include <iostream>

using namespace std;

class PlayerTank : public Tank
{
public:
      PlayerTank(); // Construtor

	  void move(); // Move tank
	  void fire(); // Fire shell
	  void reset(){}; // Reset variables

	  void decisionTree();
	  

private:
	string sCurrentState;
	void setCurrentState(string nextState);
	void makeDecision(bool decision);
	
};
#endif