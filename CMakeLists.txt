cmake_minimum_required(VERSION 3.9)
project(forever_land)

set(CMAKE_CXX_STANDARD 17)
set(ORGANIZATION_NAME "Arctic Fox Studio, LTD")

find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} {SDL2NET_INCLUDE_DIRS} {Boost_INCLUDE_DIRS})

add_executable(forever_land
        Main.cpp net/Server.cpp net/Server.hpp net/Client.cpp net/Client.hpp health/System.cpp health/System.hpp)
target_link_libraries(forever_land ${Boost_LIBRARIES} ${SDL2_LIBRARIES} -lSDL2_net)


