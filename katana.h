#ifndef _KATANA_H                 // Prevent multiple definitions if this 
#define _KATANA_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "Player.h"

namespace katanaNS
{
	const int WIDTH = 149;                   // image width
	const int HEIGHT = 8;                  // image height
	const float ROTATION_RATE = 360.0;  // degrees per second
	const float SPEED = 300;                // 10 pixels per second
	const float MASS = 300.0f;              // mass
	const float SCALE = 1.4;
	
	const float SWING_START = -80;
	const float SWING_END = 30;

	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   KATANA_RIGHT_FRAME = 0;      // sword starts at frame 0
	const int   KATANA_LEFT_FRAME = 1;         // sword animation frames 0
}

class Katana : public Entity
{
public:
    // constructor
    Katana();

    // inherited member functions
    void update(float frameTime);
	void setPlayer(Player* p){player = p;}

private:
	Player* player;
	float swingAngle;
	float timeSinceSwing;
};

#endif