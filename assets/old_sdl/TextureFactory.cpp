#include "TextureFactory.hpp"
#include "GameException.hpp"
#include "MemoryException.hpp"
#include "Logger.hpp"
#include <sstream>

TextureFactory::TextureFactory() {

}

Texture * TextureFactory::checkoutTexture(SDL_Renderer * pRenderer, const char * filename) {
   Texture * pTexture = NULL;
   TextureFactoryData * pTextureFactoryData = NULL;

   // First look to see if the texture is loaded, if not - load it.
   for (std::vector<TextureFactoryData *>::iterator it = _textureData.begin(); it != _textureData.end(); ++it) {
      if ((*it)->textureName.compare(filename) == 0) {
         (*it)->numCheckouts++;
         return (*it)->pTexture;
      }
   }

   // Load the texutre
   try {
      std::stringstream string;

      if ((pTextureFactoryData = new TextureFactoryData()) == NULL) {
         string << "Error allocating texture factory data";
         throw memoryException(string.str().c_str(), GameExceptionSeverity_Error);
      }

      if ((pTexture = new Texture()) == NULL) {
         string << "Error allocating texture " << filename;
         throw memoryException(string.str().c_str(), GameExceptionSeverity_Error);
      }
      pTexture->loadTexture(pRenderer, filename);

   }
   catch (GameException & e) {
      std::string string;
      if (e.getExceptionSeverity() != GameExceptionSeverity_Info) {
         
         // Log the error
         e.getExceptionString(string);
         globalLogger->logError(string);

         if (pTextureFactoryData != NULL) {
            delete pTextureFactoryData;
         }

         if (pTexture != NULL) {
            pTexture->unloadTexture();
            delete pTexture;
         }

         return NULL;
      }
   }

   pTextureFactoryData->pTexture = pTexture;
   pTextureFactoryData->numCheckouts = 0;
   pTextureFactoryData->textureName = filename;

   _textureData.push_back(pTextureFactoryData);

   return pTexture;
}

void TextureFactory::checkinTexture(Texture * pTexture) {
   // First look to see if the texture is loaded, if not - load it.
   for (std::vector<TextureFactoryData *>::iterator it = _textureData.begin(); it != _textureData.end(); ++it) {
      if ((*it)->pTexture == pTexture) {
         (*it)->numCheckouts--;
         if ((*it)->numCheckouts == 0) {
            (*it)->pTexture->unloadTexture();
            delete (*it)->pTexture;
            delete (*it);
            it = _textureData.erase(it);
         }
      }
   }
}

void TextureFactory::unloadTextures() {
   for (std::vector<TextureFactoryData *>::iterator it = _textureData.begin(); it != _textureData.end(); ++it) {
      (*it)->pTexture->unloadTexture();
      delete (*it)->pTexture;
      delete (*it);
      it = _textureData.erase(it);
   }
}
