#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){

}
Game::~Game(){

}
void Game::Init(const char* title , int x , int y , int width , int height , bool isFullScreen){
    int flags = 0;
    if(isFullScreen)
        flags = SDL_WINDOW_FULLSCREEN; 
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout<<"subsytems initialized."<<std::endl;
        window = SDL_CreateWindow(title , x , y , width , height , flags);
        if(window)
            std::cout<<"window is created"<<std::endl;
        renderer = SDL_CreateRenderer(window , -1 , 0);
        if(renderer)
            std::cout<<"renderer is created"<<std::endl;
        isRunning = true;
    }
    else{
        isRunning = false;
    }

}
void Game::HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT: isRunning = false;
            break;
    }
}
void Game::Update(){

}
void Game::Render(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
void Game::Clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
bool Game::Running(){
    return isRunning;
}
