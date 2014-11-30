// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 entity.h v1.3
// Added Pixel Perfect collision function. (Mar-22-2013)

#ifndef _ENTITY_H               // Prevent multiple definitions if this 
#define _ENTITY_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Entity;

#include "image.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
    enum COLLISION_TYPE {NONE, CIRCLE, BOX, ROTATED_BOX, PIXEL_PERFECT};
    const float GRAVITY = 6.67428e-11f;         // gravitational constant
	enum direction {none, up, down, left, right};
}

class Entity : public Image
{
    // Entity properties
private:
	VECTOR2 position;

  protected:
    entityNS::COLLISION_TYPE collisionType;
    VECTOR2 center;         // center of entity
    VECTOR2 collisionCenter;    // center of collision
    float   radius;         // radius of collision circle
    VECTOR2 distSquared;    // used for calculating circle collision
    float   sumRadiiSquared;
    // edge specifies the collision box relative to the center of the entity.
    // left and top are typically negative numbers
    RECT    edge;           // for BOX and ROTATED_BOX collision detection
    VECTOR2 corners[4];     // for ROTATED_BOX collision detection
    VECTOR2 edge01,edge03;  // edges used for projection
    float   edge01Min, edge01Max, edge03Min, edge03Max; // min and max projections
    VECTOR2 velocity;       // velocity
    VECTOR2 deltaV;         // added to velocity during next call to update()
    float   mass;           // Mass of entity
    float   health;         // health 0 to 100
    float   rr;             // Radius squared variable
    float   force;          // Force of gravity
    float   gravity;        // gravitational constant of the game universe
    Input   *input;         // pointer to the input system
    HRESULT hr;             // standard return type
    bool    active;         // only active entities may collide
    bool    rotatedBoxReady;    // true when rotated collision box is ready
    DWORD   pixelsColliding;    // number of pixels colliding in pixel perfect collision

    // --- The following functions are protected because they are not intended to be
    // --- called from outside the class.
    // Circular collision detection 
    // Pre: &ent = Other entity
    // Post: &collisionVector is from center to center
    virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
    // Axis aligned box collision detection
    // Pre: &ent = Other entity
    // Post: &collisionVector is from center to center
    virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection between boxes
    // Pre: &ent = Other entity
    // Post: &collisionVector is perpendicular to collision edge
    virtual bool collideRotatedBox(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection between box and circle
    // Pre: &ent = Other entity
    // Post: &collisionVector is perpendicular to collision edge or
    //       center to corner when collision is with box corner.
    virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection helper functions
    void computeRotatedBox();
    bool projectionsOverlap(Entity &ent, VECTOR2 &collisionVector);
    bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);
    // Pixel Perfect collision detection
    // If the graphics card does not support a stencil buffer then CIRCLE
    // collision is used.
    // Pre: &ent = Other entity
    // Post: &collisionVector contains collision vector
    virtual bool collidePixelPerfect(Entity &ent, VECTOR2 &collisionVector);

  public:
    // Constructor
    Entity();
    // Destructor
    virtual ~Entity() {}

    ////////////////////////////////////////
    //           Get functions            //
    ////////////////////////////////////////

    // Return center of scaled Entity as screen x,y.
    virtual const VECTOR2* getCenter()   
    {
        center = VECTOR2(getCenterX(),getCenterY());
        return &center;
    }

	   virtual const VECTOR2 getCenterPoint()   
    {
        center = VECTOR2(getCenterX(),getCenterY());
        return center;
    }

    // Return collision center
    virtual const VECTOR2* getCollisionCenter()
    { return &collisionCenter; }

    // Return radius of collision circle.
    virtual float getRadius() const     {return radius;}

    // Return RECT structure used for BOX and ROTATED_BOX collision detection.
    virtual const RECT& getEdge() const {return edge;}

    // Return corner c of ROTATED_BOX
    virtual const VECTOR2* getCorner(UINT c) const
    {
        if(c>=4) 
            c=0;
        return &corners[c]; 
    }

    // Return velocity vector.
    virtual const VECTOR2 getVelocity() const {return velocity;}

    // Return active.
    virtual bool  getActive()         const {return active;}

    // Return mass.
    virtual float getMass()           const {return mass;}

    // Return gravitational constant.
    virtual float getGravity()        const {return gravity;}

    // Return health;
    virtual float getHealth()         const {return health;}

    // Return collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

    // Return number of pixels colliding in pixel perfect collision
    virtual DWORD getpixelsColliding() const {return pixelsColliding;}

	VECTOR2 getPosition() {return position;}
	float getPositionX() {return position.x;}
	float getPositionY() {return position.y;}

    ////////////////////////////////////////
    //           Set functions            //
    ////////////////////////////////////////

    // Set velocity.
    virtual void  setVelocity(VECTOR2 v)    {velocity = v;}

    // Set delta velocity. Added to velocity in update().
    virtual void  setDeltaV(VECTOR2 dv)     {deltaV = dv;}

    // Set active.
    virtual void  setActive(bool a)         {active = a;}

    // Set health.
    virtual void setHealth(float h)         {health = h;}

    // Set mass.
    virtual void  setMass(float m)          {mass = m;}

    // Set gravitational constant. Default is 6.67428e-11
    virtual void  setGravity(float g)       {gravity = g;}

    // Set radius of collision circle.
    virtual void setCollisionRadius(float r)    {radius = r;}

    // Set collision center
    virtual void setCollisionCenter(VECTOR2 cc) {collisionCenter = cc;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    virtual void setEdge(RECT e)    {edge = e;}

    // Set rotatedBoxReady. Set to false to force recalculation.
    virtual void setRotatedBoxReady(bool r) {rotatedBoxReady = r;}

	void setPosition(VECTOR2 pos) {position = pos;}
	void setPositionX(float pos) {position.x = pos;}
	void setPositionY(float pos) {position.y = pos;} 
	void incPositionX(float pos) {position.x += pos;}
	void incPositionY(float pos) {position.y += pos;}
	void incPosition(VECTOR2 pos) {position += pos;}


    ////////////////////////////////////////
    //         Other functions            //
    ////////////////////////////////////////

    // Update Entity.
    // typically called once per frame
    // frameTime is used to regulate the speed of movement and animation
    virtual void update(float frameTime);

    // Initialize Entity
    // Pre: *gamePtr = pointer to Game object
    //      width = width of Image in pixels  (0 = use full texture width)
    //      height = height of Image in pixels (0 = use full texture height)
    //      ncols = number of columns in texture (1 to n) (0 same as 1)
    //      *textureM = pointer to TextureManager object
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    // Activate Entity.
    virtual void activate();

    // Empty ai function to allow Entity objects to be instantiated.
    virtual void ai(float frameTime, Entity &ent);

    // Is this entity outside the specified rectangle?
    virtual bool outsideRect(RECT rect);

    // Does this entity collide with ent?
    virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

    // Damage this Entity with weapon.
    virtual void damage(int weapon);

    // Entity bounces after collision with other Entity
    void bounce(VECTOR2 &collisionVector, Entity &ent);

    // Adds the gravitational force to the velocity vector of this entity
    void gravityForce(Entity *other, float frameTime);
};

#endif
