#pragma once
#include"Action.h"
class Exit : public Action
{
	
public:
	Exit(ApplicationManager* pApp);

	//Reads ellipse parameters
	virtual void ReadActionParameters();

	//Add ellipse to the ApplicationManager
	virtual void Execute();
	
};
