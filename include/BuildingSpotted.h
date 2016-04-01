#pragma once

#include "Action.h"

class BuildingCheck : public BehaviourTree::Sequence {
private:

public:

};

class Score_Condition : public Condition {
public:
	virtual bool run() override{
		std::cout << "Enemy Winning\n";
		return true;
	}
};




