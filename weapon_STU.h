#ifndef _WEAPON_H
#define _WEAPON_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"

namespace weaponNS{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 64;                  // image height
	const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
	const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 750;

	const int TEXTURE_COL = 4;
	const float SCALE = 1.0f;
}

class Weapon: public Entity{
private:
	entityNS::direction facingDir;
public:
	Weapon();
};

#endif