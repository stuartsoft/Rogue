#include "guard.h"

Guard::Guard(){
	spriteData.width = guardNS::WIDTH;           // size of Ship1
	spriteData.height = guardNS::HEIGHT;
	spriteData.x = guardNS::X;                   // location on screen
	spriteData.y = guardNS::Y;
	spriteData.rect.bottom = guardNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = guardNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = guardNS::WIDTH/2.0;
	setScale(guardNS::SCALE);

	mass = guardNS::MASS;
	edge.top = -guardNS::HEIGHT/2;
	edge.bottom = guardNS::HEIGHT/2;
	edge.left = -20;
	edge.right = 20;
	collisionType = entityNS::BOX;

	health = guardNS::MAX_HEALTH;

	facingDir = entityNS::direction::none;
}

void Guard::draw(VECTOR2 cam){
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Guard::update(float frameTime){
	Entity::update(frameTime);

	incPosition(D3DXVECTOR2(velocity*frameTime));
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}