
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef CRATE_H                 // Prevent multiple definitions if this 
#define CRATE_H   
class Crate;

#include "entity.h"
#include "constants.h"

namespace CrateNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
}

// inherits from Entity class
class Crate : public Entity
{
private:
   // puckNS::DIRECTION direction;    
    bool collision;                 
    bool target;  
	int directionX;
	int directionY;

public:
    // constructor
    Crate();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

	void draw(VECTOR2 cam);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

};
#endif

