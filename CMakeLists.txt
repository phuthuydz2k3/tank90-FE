# Initial CMake configuration
cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

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
)

# Link against the SDL2 library
target_link_libraries(Tank98 SDL2::SDL2)
