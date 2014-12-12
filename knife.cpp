#include "Knife.h"


Knife::Knife(){
	edge.top = -weaponNS::HEIGHT/2;
	edge.bottom = weaponNS::HEIGHT/2;
	edge.left = -weaponNS::WIDTH/2;
	edge.right = weaponNS::WIDTH/2;
	collisionType = entityNS::BOX;
}

void Knife::draw(VECTOR2 cam){
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Knife::update(float frameTime){
    Entity::update(frameTime);

	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));

	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}