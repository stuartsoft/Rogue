#ifndef _GRENADE_H                 // Prevent multiple definitions if this 
#define _GRENADE_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "weapon.h"

namespace GrenadeNS
{
	const float fusetime = 2.0f;
}

class Grenade : public Weapon
{
private:
	float fuse;
public:
    // constructor
    Grenade();

	void draw(VECTOR2 cam);
    // inherited member functions
	void update(float frameTime);
	float getFuse(){return fuse;};
	void resetFuse(){fuse = GrenadeNS::fusetime;};

};

#endif