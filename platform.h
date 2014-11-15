#ifndef _PLATFORM_H
#define _PLATFORM_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace Platformns{
    const int WIDTH =512;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
}

class Platform: public Entity{
private:
public:
	Platform();
	void Platform::draw();
	void Platform::update(float frameTime);
};

#endif