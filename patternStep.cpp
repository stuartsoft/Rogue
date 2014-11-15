#include "patternStep.h"

PatternStep::PatternStep()
{
    active = false;                 
	timeInStep = 0;
	entity = NULL;  
	timeForStep = 0;
	action = NONE;
}

void PatternStep::initialize(Entity *e) // FIX THIS
{
	entity = e;
}

void PatternStep::update(float frameTime)
{
	if (!active) return;
	timeInStep += frameTime;
	
	if(timeInStep > timeForStep)
	{
		timeInStep = 0;
		active = false;
	}

	switch (action)
	{
	case NONE:
		entity->setVelocity(D3DXVECTOR2(0,0));
		break;
	case RIGHT:
		entity->setVelocity(D3DXVECTOR2(1,0));
		break;
	case LEFT:
		entity->setVelocity(D3DXVECTOR2(-1,0));
		break;
	}
}