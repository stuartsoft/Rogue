#include "Crate.h"

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

	edge.top = -CrateNS::HEIGHT/2;
	edge.bottom = CrateNS::HEIGHT/2;
	edge.left = -CrateNS::WIDTH/2;
	edge.right = CrateNS::WIDTH/2;
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
    Entity::update(frameTime);
	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));
	
	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
}

