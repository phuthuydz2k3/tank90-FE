cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)

include (FindPkgConfig)
include (FindSDL_net)

# Find the SDL2 and SDL2_mixer libraries
find_package(SDL2 REQUIRED)
pkg_search_module (SDL_NET REQUIRED SDL2_net)

include_directories(${CMAKE_SOURCE_DIR}/Source)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL_NET_INCLUDE_DIRS})

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
        Source/Game/Manager/LoadResourceManager.cpp
        Source/Game/Manager/LoadResourceManager.h
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
        Source/Game/Entities/Brick.cpp
        Source/Game/Entities/Brick.h
        Source/Game/Components/RectangleCollider.cpp
        Source/Game/Components/RectangleCollider.h
        Source/Game/Systems/RectangleColliderSystem.cpp
        Source/Game/Systems/RectangleColliderSystem.h
        Source/Game/Common/ColliderLayer.h
        Source/Game/Entities/Tree.cpp
        Source/Game/Entities/Tree.h
        Source/Game/Manager/SoundManager.cpp
        Source/Game/Manager/SoundManager.h
        Source/Game/Components/Effect.cpp
        Source/Game/Components/Effect.h
        Source/Game/Components/Effect.cpp
        Source/Game/Entities/CollideExplosion.cpp
        Source/Game/Entities/CollideExplosion.h
        Source/Game/Systems/EffectSystem.cpp
        Source/Game/Systems/EffectSystem.h
        Source/Game/Entities/SpawnPoint.cpp
        Source/Game/Entities/SpawnPoint.h
        Source/Game/Entities/Wall.cpp
        Source/Game/Entities/Wall.h
        Source/Game/Services/GameplayService.cpp
        Source/Game/Services/GameplayService.h
        Source/Game/Components/NetworkTracking.cpp
        Source/Game/Components/NetworkTracking.h
        Source/Game/Systems/NetworkTrackingSystem.cpp
        Source/Game/Systems/NetworkTrackingSystem.h
        Source/Game/Common/TankStatePacket.h
        Source/Game/Components/NetworkReceiver.cpp
        Source/Game/Components/NetworkReceiver.h
        Source/Game/Systems/NetworkReceiverSystem.cpp
        Source/Game/Systems/NetworkReceiverSystem.h
        Source/Game/Feature/BeDestroy.cpp
        Source/Game/Feature/BeDestroy.h
)
add_executable(Server Source/Server.cpp
        Source/Game/Feature/BeDestroy.cpp
        Source/Game/Feature/BeDestroy.h
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

target_link_libraries(Server SDL2::SDL2 ${SDL_NET_LIBRARIES})
# Link against the SDL2 and SDL2_mixer libraries
target_link_libraries(Tank98 SDL2::SDL2 SDL2_image SDL2_mixer ${SDL_NET_LIBRARIES})