#include "WorldObject.hpp"
#include <math.h>

WorldObject::WorldObject() :
_previousPosition(0, 0), _position(0, 0), _velocity(0, 0),
_acceleration(0, 0), _radius(0), _mass(0), _delta(0) {
}

WorldObject::~WorldObject() {
   // Nothing for now
}

bool WorldObject::collision(WorldObject * worldObject) {
   double xSq = (this->_position.x - worldObject->_position.x) *
      (this->_position.x - worldObject->_position.x);

   double ySq = (this->_position.y - worldObject->_position.y) *
      (this->_position.y - worldObject->_position.y);

   double rSq = (this->_radius + worldObject->_radius) *
      (this->_radius + worldObject->_radius);

   return (xSq + ySq <= rSq);
}

double WorldObject::force(WorldObject * worldObject) {
   double distSq = _position.distanceSquared(worldObject->_position);
   return GRAVITATIONAL_CONSTANT * ((_mass * worldObject->_mass) / distSq);
}

double WorldObject::acceleration(WorldObject * worldObject) {
   double distSq = _position.distanceSquared(worldObject->_position);
   return GRAVITATIONAL_CONSTANT * (worldObject->_mass / distSq);
}

void WorldObject::applyGravity(WorldObject * worldObject) {
   Vector2D lastAcceleration = _acceleration;
   Vector2D tmpAcceleration;
   double dx, dy;
   double angle;
   double distSq = _position.distanceSquared(worldObject->_position);
   double force;
   double dt = _delta * .001;

   _position.x += _velocity.x * dt + (lastAcceleration.x * dt * dt);
   _position.y += _velocity.y * dt + (lastAcceleration.y * dt * dt);

   dx = worldObject->_position.x - _position.x;
   dy = worldObject->_position.y - _position.y;

   angle = SDL_atan2(dy, dx);

   force = this->force(worldObject);

   tmpAcceleration.x = (force / _mass) * SDL_cos(angle);
   tmpAcceleration.y = (force / _mass) * SDL_sin(angle);

   _acceleration.x = (lastAcceleration.x + tmpAcceleration.x) / 2.0f;
   _acceleration.y = (lastAcceleration.y + tmpAcceleration.y) / 2.0f;

   _velocity.x += _acceleration.x * dt;
   _velocity.y += _acceleration.y * dt;
}

void WorldObject::setRadius(double radius) {
   _radius = radius;
}

void WorldObject::setMass(double mass) {
   _mass = mass;
}

void WorldObject::setPosition(Vector2D & position) {
   _position = position;
}

void WorldObject::setPosition(double x, double y) {
   _position.x = x;
   _position.y = y;
}

void WorldObject::setVelocity(Vector2D & velocity) {
   _velocity = velocity;
}

void WorldObject::setVelocity(double x, double y) {
   _velocity.x = x;
   _velocity.y = y;
}

void WorldObject::update(Uint64 dt) {
   _delta = dt;
}

void WorldObject::getPosition(Vector2D & position) {
   position = _position;
}
