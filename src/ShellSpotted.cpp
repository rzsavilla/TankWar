#include "CheckShell.h"

CheckShell::CheckShell(SmartTank* ptr_tank)
	: canAvoid(new CanAvoidCondition(ptr_tank))
{
	this->addChild(canAvoid);
}

CheckShell::~CheckShell()
{
	delete canAvoid;
}