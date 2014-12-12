#include "Grenade.h"


Grenade::Grenade(){
	fuse = GrenadeNS::fusetime;
	edge.top = -weaponNS::HEIGHT/2;
	edge.bottom = weaponNS::HEIGHT/2;
	edge.left = -16;
	edge.right = 22;
	collisionType = entityNS::BOX;
}

void Grenade::draw(VECTOR2 cam){
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Grenade::update(float frameTime){
	float DragConstant = 2.0f;
    Entity::update(frameTime);
	if (abs(velocity.x)>2.0f || abs(velocity.y)>2.0f){
		if(velocity.x>0)
			velocity.x-=DragConstant;
		else
			velocity.x+=DragConstant;
		if (velocity.y>0)
			velocity.y-=DragConstant;
		else
			velocity.y+=DragConstant;
	}
	if (D3DXVec2Length(&velocity)<3.0f){
		velocity = VECTOR2(0,0);
	}

	fuse-=frameTime;
	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));

	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}