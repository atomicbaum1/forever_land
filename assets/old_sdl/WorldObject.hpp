#ifndef __WORLD_OBJECT__
#define __WORLD_OBJECT__

#include "Vector2d.hpp"
#include "Updatable.hpp"

#define GRAVITATIONAL_CONSTANT 6.6742e-11
#define PI 3.141592654

/*
* Notes:
* -> Until we need anything else, everything in our world is a circle.
*/

class WorldObject : public IUpdatable {
protected:
   Vector2D _previousPosition;
   Vector2D _position;
   Vector2D _velocity;
   Vector2D _acceleration;
   double _radius;
   double _mass;
   Uint64 _delta;

public:
   WorldObject();
   virtual ~WorldObject();

   // Collision
   virtual bool collision(WorldObject * worldObject);
   virtual double force(WorldObject * worldObject);
   virtual double acceleration(WorldObject * worldObject);

   // Apply gravity to us by worldObject passed
   virtual void applyGravity(WorldObject * worldObject);

   // Set functions
   virtual void setRadius(double radius);
   virtual void setMass(double mass);
   virtual void setPosition(Vector2D & position);
   virtual void setPosition(double x, double y);
   virtual void setVelocity(Vector2D & velocity);
   virtual void setVelocity(double x, double y);

   // Get functions
   virtual void getPosition(Vector2D & position);

   // Update
   virtual void update(Uint64 dt);
};

#endif
