# Initial CMake configuration
cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)

# Find the SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/Source)
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
        Source/Game/Components/Transform.cpp
        Source/Game/Components/Transform.h
        Source/Game/Components/Sprite.cpp
        Source/Game/Components/Sprite.h
        Source/Game/LoadResourceManager.cpp
        Source/Game/LoadResourceManager.h
        Source/Game/Entities/Tank.cpp
        Source/Game/Entities/Tank.h
        Source/Game/Systems/SpriteSystem.cpp
        Source/Game/Systems/SpriteSystem.h
        Source/Game/Common/Time.cpp
        Source/Game/Common/Time.h
        Source/Game/Components/ControlComponent.cpp
        Source/Game/Components/ControlComponent.h
        Source/Game/Systems/ControlSystem.cpp
        Source/Game/Systems/ControlSystem.h
        Source/Game/Entities/Bullet.cpp
        Source/Game/Entities/Bullet.h
        Source/Game/Components/FlyComponent.cpp
        Source/Game/Components/FlyComponent.h
        Source/Game/Components/DestroyCounter.cpp
        Source/Game/Components/DestroyCounter.h
        Source/Game/Systems/FlySystem.cpp
        Source/Game/Systems/FlySystem.h
        Source/Game/Systems/DestroyCounterSystem.cpp
        Source/Game/Systems/DestroyCounterSystem.h
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# Link against the SDL2 library
target_link_libraries(Tank98 SDL2::SDL2 SDL2_image)
