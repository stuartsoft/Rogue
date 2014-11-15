#include "platform.h"

Platform::Platform(){
	spriteData.width = Platformns::WIDTH;           // size of Ship1
	spriteData.height = Platformns::HEIGHT;
	spriteData.x = Platformns::X;                   // location on screen
	spriteData.y = Platformns::Y;
	spriteData.rect.bottom = Platformns::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Platformns::WIDTH;
	edge.top = -Platformns::HEIGHT/2;
	edge.bottom = Platformns::HEIGHT/2;
	edge.left = -Platformns::WIDTH/2;
	edge.right = Platformns::WIDTH/2;
	collisionType = entityNS::BOX;
}

void Platform::draw()
{
	Image::draw();              // draw Player
}

void Platform::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += velocity.x*frameTime;
	spriteData.y += velocity.y*frameTime;
}