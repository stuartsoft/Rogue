#include "C4.h"


C4::C4(){
	fuse = C4NS::fusetime;
	setFrames(1,2);
}

void C4::draw(VECTOR2 cam){
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void C4::update(float frameTime){
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
	setFrameDelay(fuse/10);
	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));

	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}