#ifndef _GRENADE_H                 // Prevent multiple definitions if this 
#define _GRENADE_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "weapon.h"

namespace KnifeNS
{
}

class Knife : public Weapon
{
private:
public:
    // constructor
    Knife();

	void draw(VECTOR2 cam);
    // inherited member functions
	void update(float frameTime);

};

#endif