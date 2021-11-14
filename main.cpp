//상속, 다형성
//추상클래스,Vector2D
//물리, 키입력
//

#include <SDL.h>
#include<SDL_image.h>
#include"Game.h"
#include"InputHandler.h"

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
 const int SCREEN_WIDTH = 1600;
 const int SCREEN_HEIGHT = 900;

 const int FPS = 60;
 const int DELAY_TIME = 1000.0f/FPS;
Game* game = nullptr;

int main(int argc, char* args[])
{

    game = Game::Instance();
    game->Init("Game Class", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 frameStart, frameTime;
    while (Game::Instance()->running()) {

        frameStart = SDL_GetTicks();

        Game::Instance()->handleEvents();
        Game::Instance()->Update();
        Game::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }

    }
    Game::Instance()->clean();
    InputHandler::Instance()->clean();
    SDL_Delay(500);
    SDL_Quit();

    return 0;
}