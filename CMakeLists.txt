# Initial CMake configuration
cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)
include (FindPkgConfig)
include (FindSDL_net)

# Find the SDL2 library
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
pkg_search_module (SDL2 REQUIRED sdl2)
pkg_search_module (SDL_NET REQUIRED SDL2_net)

include_directories (${SDL2_INCLUDE_DIRS} ${SDL_NET_INCLUDE_DIRS})

# Add the executable
add_executable(Tank98 Source/main.cpp Source/Math/Vector2.cpp
        Source/SingletonTemplate.h
        Source/Math/Vector2.h
        Source/ECS/Component/Component.cpp
        Source/ECS/Component/Component.h
        Source/ECS/Entity/Entity.cpp
        Source/ECS/Entity/Entity.h
        Source/ECS/Entity/EntityManager.cpp
        Source/ECS/Entity/EntityManager.h
        Source/ECS/System/System.cpp
        Source/ECS/System/System.h
        Source/ECS/System/SystemManager.cpp
        Source/ECS/System/SystemManager.h
        Source/main.cpp
)

# Add the server executable
add_executable(Server Source/server.cpp)

# Link against the SDL2 library
target_link_libraries(Tank98 ${SDL2_LIBRARIES} ${SDL_NET_LIBRARIES})
target_link_libraries(Server ${SDL2_LIBRARIES} ${SDL_NET_LIBRARIES})
