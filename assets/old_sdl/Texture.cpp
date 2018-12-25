#include "Texture.hpp"
#include "SDLIncludes.hpp"
#include <sstream>

Texture::Texture() : _pTexture(NULL), _width(0), _height(0) {
   memset(&_sourceRectangle, 0, sizeof (struct SDL_Rect));
   memset(&_destRectangle, 0, sizeof (struct SDL_Rect));
}

Texture::~Texture() {
   unloadTexture();
}

void Texture::loadTexture(SDL_Renderer * renderer, const char * filename) {
   SDL_Surface * surface;
   std::stringstream error;

   // First load the surface
   if ((surface = IMG_Load(filename)) == NULL) {
      error << "Could not load image \"" << filename <<  "\": " <<  IMG_GetError() << "\n";

      throw textureException(error.str().c_str(), GameExceptionSeverity_Error);
      return;
   }

   // Turn it into a texture
   if ((_pTexture = SDL_CreateTextureFromSurface(renderer, surface)) == NULL) {
      error << "Could not turn surface into texture: " << SDL_GetError() << "\n";
      SDL_FreeSurface(surface);
      throw textureException(error.str().c_str(), GameExceptionSeverity_Error);
      return;
   }

   // Width and height
   _width = surface->w;
   _height = surface->h;

   // Setup the rectangle
   _sourceRectangle.x = 0;
   _sourceRectangle.y = 0;
   _sourceRectangle.w = surface->w;
   _sourceRectangle.h = surface->h;
   _destRectangle.x = 0;
   _destRectangle.y = 0;
   _destRectangle.w = surface->w;
   _destRectangle.h = surface->h;

   // Free the surface
   SDL_FreeSurface(surface);
}

void Texture::unloadTexture() {
   if (_pTexture != NULL) {
      SDL_DestroyTexture(_pTexture);
      _pTexture = NULL;
   }
}

void Texture::render(SDL_Renderer * renderer) {
   if (SDL_RenderCopy(renderer, _pTexture, &_sourceRectangle, &_destRectangle) != 0) {
      std::stringstream error;
      error << "Rendering error " << SDL_GetError() << "\n";
      throw textureException(error.str().c_str(), GameExceptionSeverity_Error);
   }
}

void Texture::updateSourceRectangle(SDL_Rect * rectangle) {
   memcpy(&_sourceRectangle, rectangle, sizeof (struct SDL_Rect));
}

void Texture::updateSourceRectangle(unsigned int width, unsigned int height, int x, int y) {
   _sourceRectangle.w = width;
   _sourceRectangle.h = height;
   _sourceRectangle.x = x;
   _sourceRectangle.y = y;
}

void Texture::updateDestRectangle(SDL_Rect * rectangle) {
   memcpy(&_destRectangle, rectangle, sizeof (struct SDL_Rect));
}

void Texture::updateDestRectangle(unsigned int width, unsigned int height, int x, int y) {
   _destRectangle.w = width;
   _destRectangle.h = height;
   _destRectangle.x = x;
   _destRectangle.y = y;
}

int Texture::getWidth() {
   return _width;
}

int Texture::getHeight() {
   return _height;
}

TextureException::TextureException(const char * file, const char * function, unsigned int line,
   const char * message, GameExceptionSeverity severity) : GameException(file, function, line, message, severity) {

}
