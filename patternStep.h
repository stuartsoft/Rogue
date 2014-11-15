#define WIN32_LEAN_AND_MEAN
#ifndef PATTERN_STEM_H                 // Prevent multiple definitions if this 
#define PATTERN_STEM_H   

//class PatternStep;

#include "constants.h"
#include "entity.h"
#include <cmath>
#include <d3d9.h>
#include <d3dx9.h>
//#include "bricks.h"

namespace patternStepNS
{
}

class PatternStep
{
private:
	bool active;
	float timeInStep; //accumulates the time step has executed
	Entity *entity; // FIX THIS
	float timeForStep; //limit on the time for the step
	PATTERN_STEP_ACTION action;
	
public:
    PatternStep();
    void initialize(Entity *e); // FIX THIS
    void update(float frameTime);
	void setEntity(Entity *e) {entity = e;} // FIX THIS
	void setAction(PATTERN_STEP_ACTION a) {action = a;}
	void setTimeForStep(float time) {timeForStep = time;}
	bool isFinished() {return !active;}
	void setActive() {active = true;}
	void setInactive() {active = false;}
};
#endif