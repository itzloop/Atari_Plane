#include "Game.h"
Game *game = nullptr;
int main(int argc, char* argv[])
{
const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;



    game = new Game();  
    game->Init("Atari Plane" , SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED , 500 , 600 , false );
    while(game->Running())
    {
        game->HandleEvents();
        game->Update();
        game->Render();
        
        frameStart = SDL_GetTicks();
        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay  > frameTime)
        {
           SDL_Delay(frameDelay - frameTime );
        }
    }
    game->Clean();
    return 0;
   

}

