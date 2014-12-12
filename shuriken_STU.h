#ifndef _SHURIKEN_H                 // Prevent multiple definitions if this 
#define _SHURIKEN_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "weapon_stu.h"

namespace shurikenNS
{
}

class Shuriken : public Weapon
{
public:
    // constructor
    Shuriken();

	void draw(VECTOR2 cam);
    // inherited member functions
	void update(float frameTime);
	void testfun(){};

private:
};

#endif