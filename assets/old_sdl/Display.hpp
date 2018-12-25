#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include "SDLIncludes.hpp"
#include <string>
#include "Settings.hpp"
#include "Singleton.hpp"

#define DEFAULT_DISPLAY_TITLE "TEST TITLE"

class Display {
protected:
   DisplaySettings _displaySettings;
   SDL_Renderer * _pRenderer;
   SDL_Window * _pWindow;
   SDL_DisplayMode * _pDisplayMode;
   std::string _title;

public:
   Display(const char * title = DEFAULT_DISPLAY_TITLE);
   virtual ~Display();
   virtual void initDisplay(DisplaySettings * pDisplaySettings);
   SDL_Renderer * getRenderer() const;
   SDL_Window * getWindow() const;
   void render() const;
   void clear() const;
};

typedef Singleton<Display> GlobalDisplay;
#define globalDisplay GlobalDisplay::instance()

#endif
