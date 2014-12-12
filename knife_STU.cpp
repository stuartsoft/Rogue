#include "Knife_stu.h"


Knife::Knife(){
	//edge.top = -11;
	//edge.bottom = 11;
	//edge.left = 27;
	//edge.right = 162;
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

	setRadians(getRadians()+0.05);
	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));

	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}