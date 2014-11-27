#include "Wall.h"

//=============================================================================
// default constructor
//=============================================================================
Wall::Wall() : Entity()
{
    spriteData.width = WallNS::WIDTH;           
    spriteData.height = WallNS::HEIGHT;
    spriteData.x = WallNS::X;                   // location on screen
    spriteData.y = WallNS::Y;
    spriteData.rect.bottom = WallNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = WallNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = WallNS::WIDTH/2.0;                 // collision radius
    collision = false;
	collisionType =entityNS::BOX;// entityNS::CIRCLE;
    target = false;
	spriteData.scale = 1;

	edge.bottom = -WallNS::HEIGHT/2;
	edge.top = WallNS::HEIGHT/2;
	edge.right = -WallNS::WIDTH/2;
	edge.left = WallNS::WIDTH/2;
}

bool Wall::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = -1;
	directionX = 1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Wall::update(float frameTime)
{
    Entity::update(frameTime);

}

