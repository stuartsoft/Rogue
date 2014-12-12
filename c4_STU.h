#ifndef _C4_H                 // Prevent multiple definitions if this 
#define _C4_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "weapon_stu.h"

namespace C4NS
{
	const float fusetime = 5.0f;
}

class C4 : public Weapon
{
private:
	float fuse;
public:
    // constructor
    C4();

	void draw(VECTOR2 cam);
    // inherited member functions
	void update(float frameTime);
	float getFuse(){return fuse;};
	void resetFuse(){fuse = C4NS::fusetime;};

};

#endif