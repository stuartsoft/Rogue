#ifndef _KNIFE_H                 // Prevent multiple definitions if this 
#define _KNIFE_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "weapon_stu.h"

namespace KnifeNS
{
	const int WIDTH = 162;
	const int HEIGHT = 23;
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
	bool swinging;//knife is being swung
};

#endif