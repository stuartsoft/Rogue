#include "bullet.h"

Bullet::Bullet() : Entity()
{
	spriteData.width = bulletNS::WIDTH;           // size of Ship1
	spriteData.height = bulletNS::HEIGHT;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	spriteData.scale = bulletNS::SCALE;

	spriteData.x = 0;
	spriteData.y = 0;

	velocity.x = 0;
	velocity.y = 0;
	
	radius = (bulletNS::WIDTH + bulletNS::HEIGHT)/4.0;	
	collisionType = entityNS::CIRCLE;

	active = false;
}

void Bullet::draw()
{
	Image::draw();
}

void Bullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
    spriteData.y += frameTime * velocity.y;

	if(spriteData.x <= -100 || spriteData.x >= GAME_WIDTH+100)
	{
		active = false;
	}
}