cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (FindPkgConfig)

# Find the SDL2 and SDL2_mixer libraries
find_package(SDL2 REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Source)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
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
        Source/Game/Common/ActionStatePacket.h
        Source/Game/Common/Event.cpp
        Source/Game/Common/Event.h
        Source/Game/Systems/ClickableSystem.cpp
        Source/Game/Systems/ClickableSystem.h
        Source/Game/Manager/UIManager.cpp
        Source/Game/Manager/UIManager.h
        Source/Game/UIs/Button.cpp
        Source/Game/UIs/Button.h
        Source/Game/UIs/Clickable.h
        Source/Game/UIs/Clickable.cpp
        Source/Game/UIs/UIUnit.h
        Source/Game/UIs/UIUnit.cpp
        Source/Game/UIs/WinUI.cpp
        Source/Game/UIs/WinUI.h
        Source/Game/UIs/LoseUI.cpp
        Source/Game/UIs/LoseUI.h
        Source/Game/UIs/PauseUI.cpp
        Source/Game/UIs/PauseUI.h
        Source/Game/UIs/GameplayUI.cpp
        Source/Game/UIs/GameplayUI.h
        Source/Game/Systems/TransformSystem.cpp
        Source/Game/Systems/TransformSystem.h
        Source/Game/UIs/Image.cpp
        Source/Game/UIs/Image.h
        Source/Game/UIs/Text.cpp
        Source/Game/UIs/Text.h
        Source/Game/Systems/TextSystem.cpp
        Source/Game/Systems/TextSystem.h
        Source/Game/Entities/GameObject.cpp
        Source/Game/Entities/GameObject.h
        Source/Game/Entities/Smoke.cpp
        Source/Game/Entities/Smoke.h
        Source/Game/Entities/Mouse.cpp
        Source/Game/Entities/Mouse.h
        Source/Game/Systems/CursorSystem.cpp
        Source/Game/Systems/CursorSystem.h
        Source/Game/Components/Cursor.cpp
        Source/Game/Components/Cursor.h
        Source/Game/Systems/FootprintSystem.cpp
        Source/Game/Systems/FootprintSystem.h
        Source/Game/Components/Footprint.cpp
        Source/Game/Components/Footprint.h
        Source/Game/UIs/LeaderBoardUI.cpp
        Source/Game/UIs/LeaderBoardUI.h
        Source/app.cpp
        Source/app.h
        Source/app_state/room.cpp
        Source/app_state/room.h
        Source/app_state/appstate.h
        Source/app_state/menu.cpp
        Source/app_state/menu.h
        Source/engine/engine.cpp
        Source/engine/engine.h
        Source/engine/renderer.cpp
        Source/engine/renderer.h
        Source/engine/spriteconfig.cpp
        Source/engine/spriteconfig.h
        Source/objects/object.cpp
        Source/objects/object.h
        Source/objects/player.cpp
        Source/objects/player.h
        Source/objects/tank.cpp
        Source/objects/tank.h
        Source/appconfig.cpp
        Source/appconfig.h
)
add_executable(Server Source/server.cpp
        Source/room_manager.cpp
        Source/room_manager.h
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Link against the OpenSSL library
target_link_libraries(Server OpenSSL::SSL OpenSSL::Crypto SDL2::SDL2 ${PostgreSQL_LIBRARIES})

# Link against the SDL2, SDL2_mixer, and libpq libraries
target_link_libraries(Tank98 SDL2::SDL2 SDL2_image SDL2_mixer SDL2_ttf ${PostgreSQL_LIBRARIES})