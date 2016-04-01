#include "CheckShootTarget.h"

ShootCheck::ShootCheck(SmartTank* ptr_tank)
: tank(ptr_tank)
, hasLOS(new LOS_Condition(ptr_tank))
, aimTurret(new Aiming_Turret(ptr_tank))
{
	addChild(aimTurret);
	addChild(hasLOS);
//	addChild(shootTarget);
}

ShootCheck::~ShootCheck() {
	delete hasLOS;
	delete aimTurret;
	//delete shootTarget;
}