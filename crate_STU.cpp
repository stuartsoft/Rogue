#include "Crate_stu.h"

//=============================================================================
// default constructor
//=============================================================================
Crate::Crate() : Entity()
{
    spriteData.width = CrateNS::WIDTH;           
    spriteData.height = CrateNS::HEIGHT;
    spriteData.x = CrateNS::X;                   // location on screen
    spriteData.y = CrateNS::Y;
    spriteData.rect.bottom = CrateNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = CrateNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = CrateNS::WIDTH/2.0;                 // collision radius
    collision = false;
    target = false;
	spriteData.scale = 1;
	setScale(1.0);
	setMass(CrateNS::mass);

	edge.top = -CrateNS::HEIGHT/2;
	edge.bottom = CrateNS::HEIGHT/2;
	edge.left = -24;
	edge.right = 24;
	collisionType = entityNS::BOX;
}

bool Crate::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = -1;
	directionX = 1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


void Crate::draw(VECTOR2 cam)
{
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Crate::update(float frameTime)
{
	CollidedThisFrame = false;
	float DragConstant = 400.0f*frameTime;
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
	if (abs(velocity.x)<DragConstant*2 && abs(velocity.x)>0.01f)
		velocity.x = 0.0f;
	if (abs(velocity.y)<DragConstant*2 && abs(velocity.y)>0.01f)
		velocity.y = 0.0f;

	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));
	
	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}

