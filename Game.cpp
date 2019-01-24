#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Map.h"
#include "Vector2D.h"
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* playertexture;
SDL_Rect srcRect , destRect;
Manager manager;
auto& Player(manager.addEntity());
SDL_Event Game::event;
Map* map;

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
    map = new Map();
    Player.addComponent<TransformComponent>(100 , -300);
    Player.addComponent<SpriteComponent>("Assets/ball.png");
    Player.addComponent<KeyboardController>();

    

}
void Game::HandleEvents(){
    
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT: isRunning = false;
            break;
    }
}
void Game::Update(){
    // destRect.h = 60;
    // destRect.w = 75;
    manager.refresh();
    manager.Update();

    
    //Player.getComponent<TransformComponent>().pos.Add(Vector2D(1 , 1) );
    
    //destRect.x = newPlayer.getComponent<TransformComponent>().x();
    //destRect.y = newPlayer.getComponent<TransformComponent>().y();
   // std::cout<<player.getComponent<TransformComponent>()->pos.x<<endl;

}
void Game::Render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    Player.getComponent<SpriteComponent>().Draw();
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
