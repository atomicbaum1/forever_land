#ifndef __ASTRONOMICAL_OBJECT_HPP__
#define __ASTRONOMICAL_OBJECT_HPP__

#include "WorldObject.hpp"
#include "Texture.hpp"

enum AstronomicalCollision {
   AstronomicalCollision_Gravity,
   AstronomicalCollision_Body,
   AstronomicalCollision_None,
};

class AstronomicalObject : public WorldObject, public IRenderable{
protected:
   Texture * _pBodyTexture;
   Texture * _pGravityTexture;
   WorldObject _gravity;
   double _gravityRadius;

public:
   AstronomicalObject();
   virtual ~AstronomicalObject();

   // Init functions
   void addBodyTexture(Texture * pTexture);
   void addGravityTexture(Texture * pTexture);
   void setBodyMass(double mass);
   void setPosition(double x, double y);
   void setPosition(Vector2D & position);

   // Collision functions
   virtual bool collidedWithGravity(WorldObject * worldObject);
   virtual bool collidedWithBody(WorldObject * worldObject);
   virtual AstronomicalCollision astronomicalCollision(AstronomicalObject * astronomicalObject);

   // Draw
   virtual void render(SDL_Renderer * renderer);
};

#endif
