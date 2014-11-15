#include "life.h"

Life::Life() : Entity()
{
	spriteData.width = lifeNS::WIDTH;           // size of Ship1
	spriteData.height = lifeNS::HEIGHT;
	spriteData.rect.bottom = lifeNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = lifeNS::WIDTH;
	spriteData.scale = lifeNS::SCALE;

	spriteData.x = 0;
	spriteData.y = 0;
	velocity.x = 0;
	velocity.y = 0;

	setCurrentFrame(0);

	active = false;
}

void Life::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
    spriteData.y += frameTime * velocity.y;
}