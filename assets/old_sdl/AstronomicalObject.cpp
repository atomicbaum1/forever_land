#include "AstronomicalObject.hpp"

AstronomicalObject::AstronomicalObject() : _pBodyTexture(NULL), _pGravityTexture(NULL), _gravityRadius(0) {

}

AstronomicalObject::~AstronomicalObject() {

}

// Init functions
void AstronomicalObject::addBodyTexture(Texture * pTexture) {
   _pBodyTexture = pTexture;
   setRadius(pTexture->getWidth() / 2);
}

void AstronomicalObject::addGravityTexture(Texture * pTexture) {
   _pGravityTexture = pTexture;
   _gravity.setRadius(pTexture->getWidth() / 2);
}

void AstronomicalObject::setBodyMass(double mass) {
   setMass(mass);
}

void AstronomicalObject::setPosition(double x, double y) {
   _position.x = x;
   _position.y = y;
   _gravity.setPosition(x, y);
}

void AstronomicalObject::setPosition(Vector2D & position) {
   _position = position;
   _gravity.setPosition(position);
}

// Collision functions
bool AstronomicalObject::collidedWithGravity(WorldObject * worldObject) {
   return _gravity.collision(worldObject);
}

bool AstronomicalObject::collidedWithBody(WorldObject * worldObject) {
   return collision(worldObject);
}

AstronomicalCollision AstronomicalObject::astronomicalCollision(AstronomicalObject * astronomicalObject) {
   if (collidedWithBody(astronomicalObject)) {
      return AstronomicalCollision_Body;
   }

   if (collidedWithGravity(&astronomicalObject->_gravity)) {
      return AstronomicalCollision_Gravity;
   }
   
   return AstronomicalCollision_None;
}

// Draw
void AstronomicalObject::render(SDL_Renderer * renderer){
   // Draw based on the center of the body.  Width and height are based on the image width and height for now.
   Vector2D position;
   double width, height;

   position = _position;
   width = _pBodyTexture->getWidth();
   height = _pBodyTexture->getHeight();
   position.x -= (width / 2);
   position.y -= (height / 2);

   _pBodyTexture->updateDestRectangle(width, height, position.x, position.y);

   position = _position;
   width = _pGravityTexture->getWidth();
   height = _pGravityTexture->getHeight();
   position.x -= (width / 2);
   position.y -= (height / 2);

   _pGravityTexture->updateDestRectangle(width, height, position.x, position.y);

   _pGravityTexture->render(renderer);
   _pBodyTexture->render(renderer);
}
