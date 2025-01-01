// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
// #include <cstring>
// #include <arpa/inet.h> // Include for inet_addr and htonl
// #include <sys/socket.h>
// #include <iostream>
// #include "ECS/Entity/EntityManager.h"
// #include "ECS/System/SystemManager.h"
// #include "Game/Common/Event.h"
// #include "Game/Manager/LoadResourceManager.h"
// #include "Game/Common/Time.h"
// #include "Game/Manager/UIManager.h"
// #include "Game/Services/GameplayService.h"
// #include "Game/Systems/NetworkTrackingSystem.h"

// void Init() {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         std::cerr << "SDL haven't been initialized: " << SDL_GetError() << std::endl;
//         return;
//     }

//     if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
//         std::cerr << "SDL_image haven't been initialized: " << IMG_GetError() << std::endl;
//         SDL_Quit();
//         return;
//     }
//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
//         return;
//     }
//     if (TTF_Init() < 0) {
//         std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
//         SDL_Quit();
//         return;
//     }

//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
//         std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
//         SDL_Quit();
//         return;
//     }
//     LoadResourceManager::getInstance()->InitWindow();
//     SystemManager::getInstance()->init();
//     UIManager::getInstance()->Init();
//     GameplayService().LoadMap(1);
//     GameplayService().EnterGame();
// }

// void Update() {
//     SDL_SetRenderDrawColor(LoadResourceManager::getInstance()->GetRenderer(), 0, 0, 0, 255);
//     SystemManager::getInstance()->update();
//     EntityManager::getInstance()->lateUpdate();
//     SDL_RenderPresent(LoadResourceManager::getInstance()->GetRenderer());
//     SDL_RenderClear(LoadResourceManager::getInstance()->GetRenderer());
// }

// int main(int argc, char *argv[]) {
//     Init();
//     bool running = true;
//     Uint32 lastTime = SDL_GetTicks();
//     while (running) {
//         Uint32 currentTime = SDL_GetTicks();
//         Time::deltaTime = (currentTime - lastTime) / 1000.0f;
//         lastTime = currentTime;
//         while (SDL_PollEvent(&Event::event)) {
//             if (Event::event.type == SDL_QUIT) {
//                 running = false;
//             }
//         }
//         Update();
//         SDL_Delay(16);
//     }
//     GameplayService().outGame();
//     LoadResourceManager::getInstance()->CleanUp();
//     EntityManager::getInstance()->clearEntities();

//     return 0;
// }

#include "app.h"

int main(int argc, char *args[])
{
    App app;
    app.run();

    return 0;
}
