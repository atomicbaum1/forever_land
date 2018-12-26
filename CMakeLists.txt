cmake_minimum_required(VERSION 3.9)
project(forever_land)

set(CMAKE_CXX_STANDARD 17)
set(ORGANIZATION_NAME "Baum Network")

find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)

set(GFX ./gfx)
set(NET ./net)
set(SYSTEM ./system)
set(SYSTEM_SETTINGS ./system/settings)
set(BASIC ./basic)
set(CONTEXT ./context)
include_directories(${GFX})
include_directories(${NET})
include_directories(${SYSTEM})
include_directories(${SYSTEM_SETTINGS})
include_directories(${BASIC})
include_directories(${CONTEXT})
include_directories(${SDL2_INCLUDE_DIRS} {SDL2NET_INCLUDE_DIRS} {SDL2IMG_INCLUDE_DIRS} {Boost_INCLUDE_DIRS})

add_executable(forever_land
        Main.cpp system/System.cpp system/System.hpp net/Connection.cpp net/Connection.hpp net/UdpConnection.cpp
        net/UdpConnection.hpp context/Context.cpp context/Context.h system/Logging.hpp gfx/Sprite.cpp gfx/Sprite.hpp
        system/Exception.cpp system/Exception.hpp gfx/AnimatedSprite.cpp gfx/AnimatedSprite.hpp gfx/Textures.cpp
        gfx/Textures.hpp basic/Singleton.hpp assets/old_sdl/Dependency.hpp system/Logging.cpp
        system/settings/Settings.cpp system/settings/Settings.hpp system/settings/DisplaySettings.cpp
        system/settings/DisplaySettings.hpp gfx/Display.cpp gfx/Display.hpp)
target_link_libraries(forever_land ${Boost_LIBRARIES} ${SDL2_LIBRARIES} -lSDL2_net -lSDL2_image)

