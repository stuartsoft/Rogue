#ifndef _SHURIKEN_H                 // Prevent multiple definitions if this 
#define _SHURIKEN_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace shurikenNS
{
	const int WIDTH = 54;                   // image width
	const int HEIGHT = 54;                  // image height
	const float ROTATION_RATE = 810.0;  // radians per second
	const float SPEED = 6000;                // 10 pixels per second
	const float MASS = 300.0f;              // mass
	const float SCALE = 0.7;
	const float GRAVITY = 800;

	const float MAX_SPEED = 1500;
	
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   SHURIKEN_START_FRAME = 0;      // starts at frame 0
	const int   SHURIKEN_END_FRAME = 0;
}

class Shuriken : public Entity
{
public:
    // constructor
    Shuriken();

    // inherited member functions
    void update(float frameTime);

private:
};

#endif