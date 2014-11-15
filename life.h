#ifndef _LIFE_H                 // Prevent multiple definitions if this 
#define _LIFE_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace lifeNS
{
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const float SCALE = 0.5;
}

class Life : public Entity
{
public:
    // constructor
    Life();

    // inherited member functions
    void update(float frameTime);

private:
};

#endif