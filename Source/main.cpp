#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Math/Vector2.h"
#include "ECS/Entity/EntityManager.h"
#include "ECS/System/SystemManager.h"
#include "Game/LoadResourceManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Brick.h"
#include "Game/Entities/Tank.h"
#include "Game/Entities/Tree.h"
#include "Game/Systems/ControlSystem.h"
#include "Game/Systems/FlySystem.h"
#include "Game/Systems/RectangleColliderSystem.h"
#include "Game/Systems/SpriteSystem.h"

void Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL haven't been initialized: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image haven't been initialized: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    LoadResourceManager::getInstance()->InitWindow();
    SystemManager::getInstance()->registerSystem<SpriteSystem>();
    SystemManager::getInstance()->registerSystem<ControlSystem>();
    SystemManager::getInstance()->registerSystem<FlySystem>();
    SystemManager::getInstance()->registerSystem<RectangleColliderSystem>();
    Tank *tank = EntityManager::getInstance()->createEntity<Tank>();
    Brick *brick = EntityManager::getInstance()->createEntity<Brick>();
    Tree* tree = EntityManager::getInstance()->createEntity<Tree>();
    brick->getComponent<Transform>()->position = VECTOR2(400, 400);
    brick->getComponent<Sprite>()->layer = 2;
    tank->getComponent<Transform>()->position = VECTOR2(100, 100);
    tank->getComponent<Sprite>()->layer = 1;
    tree->getComponent<Transform>()->position = VECTOR2(200, 200);
}

void Update() {
    SDL_SetRenderDrawColor(LoadResourceManager::getInstance()->GetRenderer(), 0, 0, 0, 255);
    SystemManager::getInstance()->update();
    EntityManager::getInstance()->lateUpdate();
}

int main(int argc, char *argv[]) {
    Init();
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        Time::deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Update();
        SDL_Delay(16);
    }

    LoadResourceManager::getInstance()->CleanUp();
    EntityManager::getInstance()->clearEntities();

    return 0;
}
