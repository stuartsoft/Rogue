#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 54;                   // image width
	const int HEIGHT = 54;                  // image height

	const float SPEED = 400;                // 10 pixels per second
	const float MASS = 300.0f;              // mass
	const float SCALE = 0.7;
	const float GRAVITY = 800;

	const int   TEXTURE_COLS = 1;           // texture has 1 columns

	const float COLLISION_DAMAGE = 25;
}

class Bullet : public Entity
{
public:
    // constructor
    Bullet();

    // inherited member functions
    void update(float frameTime);
	void draw();

	void addVelY(int y) {velocity.y += y;}
	void subVelY(int y) {velocity.y -= y;}

private:
};

#endif