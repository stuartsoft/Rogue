#include "shuriken.h"


Shuriken::Shuriken(){
	edge.top = -weaponNS::HEIGHT/2;
	edge.bottom = weaponNS::HEIGHT/2;
	edge.left = -weaponNS::WIDTH/2;
	edge.right = weaponNS::WIDTH/2;
	collisionType = entityNS::BOX;
}

void Shuriken::draw(VECTOR2 cam){
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Shuriken::update(float frameTime){
	Entity::update(frameTime);
	setRadians(getRadians()+0.05);
	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));

	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}