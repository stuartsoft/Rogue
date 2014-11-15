#include "shuriken.h"

Shuriken::Shuriken() : Entity()
{
	spriteData.width = shurikenNS::WIDTH;           // size of Ship1
	spriteData.height = shurikenNS::HEIGHT;
	spriteData.rect.bottom = shurikenNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = shurikenNS::WIDTH;
	spriteData.scale = shurikenNS::SCALE;

	spriteData.x = 0;
	spriteData.y = 0;

	velocity.x = 0;
	velocity.y = 0;
	radius = (shurikenNS::WIDTH + shurikenNS::HEIGHT)/4.0;	

	collisionType = entityNS::CIRCLE;
	active = false;
}

void Shuriken::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
    spriteData.y += frameTime * velocity.y;
	
	if(spriteData.x <= -100 || spriteData.x >= GAME_WIDTH+100)
	{
		active = false;
	}

	deltaV.y = shurikenNS::GRAVITY*(frameTime);
	setDegrees(getDegrees() + shurikenNS::ROTATION_RATE*frameTime);
}