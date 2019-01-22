#include "Game.h"
Game *game = nullptr;
int main(int argc, char* argv[])
{
    game = new Game();  
    game->Init("Atari Plane" , SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED , 800 , 640 , true );
    while(game->Running())
    {
        game->HandleEvents();
        game->Update();
        game->Render();
    }
    game->Clean();
     return 0;
    //renderTexture(LoadTexture( "Images/sina.bmp", MainRenderer) , MainRenderer ,0 , 0);
    
    // MainSurface = SDL_LoadBMP("Images/sina.bmp");
    // if (!MainSurface){
    //     SDL_DestroyRenderer(MainRenderer);
    //     SDL_DestroyWindow(MainWindow);
    //     std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }
    // MainTexture = SDL_CreateTextureFromSurface(MainRenderer , MainSurface);
    // SDL_FreeSurface(MainSurface);
    // if (!MainTexture){
    //     SDL_DestroyRenderer(MainRenderer);
    //     SDL_DestroyWindow(MainWindow);
    //     std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }
    

    // //First clear the renderer
    // SDL_RenderClear(MainRenderer);
    // //Draw the texture
    // SDL_RenderCopy(MainRenderer, MainTexture, NULL, NULL);
    // //Update the screen
    
    //SDL_Delay(10000);
   

}


// SDL_Texture* LoadTexture(const std::string &file , SDL_Renderer* renderer){
//     SDL_Surface* surface = SDL_LoadBMP(file.c_str());
//     SDL_Texture* texture = nullptr;
//     if(surface){
//         texture = SDL_CreateTextureFromSurface(renderer , surface);
//         SDL_FreeSurface(surface);
//         if (!texture){
// 			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
// 		}
//     }
//     else{
//         std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//     }
//     return texture;
// }

// void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y){
// 	//Setup the destination rectangle to be at the position we want
// 	SDL_Rect destination;
	
// 	//Query the texture to get its width and height to use
// 	SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
//     destination.x = x + WINDOW_WIDTH/2 - destination.w/2;
// 	destination.y = y + WINDOW_HEIGHT/2 - destination.h/2;
// 	SDL_RenderCopy(renderer, texture, NULL, &destination);
//     SDL_RenderPresent(renderer);
    
// }