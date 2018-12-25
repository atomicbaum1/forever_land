#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include "SDLIncludes.hpp"
#include "Renderable.hpp"
#include "GameException.hpp"

class Texture : public IRenderable {
protected:
   SDL_Texture * _pTexture;
   SDL_Rect _sourceRectangle;
   SDL_Rect _destRectangle;
   int _width, _height;

public:
   Texture();
   virtual ~Texture();
   void loadTexture(SDL_Renderer * renderer, const char * filename);
   void unloadTexture();
   virtual void render(SDL_Renderer * renderer);
   void updateSourceRectangle(SDL_Rect * rectangle);
   void updateSourceRectangle(unsigned int width, unsigned int height, int x, int y);
   void updateDestRectangle(SDL_Rect * rectangle);
   void updateDestRectangle(unsigned int width, unsigned int height, int x, int y);
   int getWidth();
   int getHeight();
};

class TextureException : public GameException {
protected:
   virtual const char * getClassName() { return "TextureException"; }
public:
   TextureException(const char * file, const char * function, unsigned int line, const char * message, GameExceptionSeverity severity);
   virtual ~TextureException() {}
};

#define textureException(message, severity) TextureException(__FILE__, __FUNCTION__, __LINE__, message, severity)

#endif
