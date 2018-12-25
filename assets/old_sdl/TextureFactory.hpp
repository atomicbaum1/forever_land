#ifndef __TEXTURE_FACTORY_HPP__
#define __TEXTURE_FACTORY_HPP__

#include <vector>
#include "Singleton.hpp"
#include "Texture.hpp"

/*
In the future it would be better to load all of the textures at game start and reference them by some ID system.
*/

typedef struct TextureFactoryData {
   Texture * pTexture;
   std::string textureName; // TextureID in the future?
   unsigned int numCheckouts;
} TextureFactoryData;

class TextureFactory {
private:
   std::vector<TextureFactoryData *> _textureData;

public:
   TextureFactory();
   Texture * checkoutTexture(SDL_Renderer * pRenderer, const char * filename);
   void checkinTexture(Texture * pTexture);
   void unloadTextures();
   /*
   Something like this:
   void loadTextures(const char * filename);
   Texture * checkoutTexture(TextureID textureId);
   void unloadTextures();
   */
};

typedef Singleton<TextureFactory> GlobalTextureFactory;
#define globalTextureFactory GlobalTextureFactory::instance()

#endif
