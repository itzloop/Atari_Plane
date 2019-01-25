#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* playertexture;
SDL_Rect srcRect , destRect;
bool Game::isFired = false;
Manager manager;
auto& Player(manager.addEntity());
auto& Boat(manager.addEntity());
auto& Chopter(manager.addEntity());
auto& Fuel(manager.addEntity());
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
    Player.addComponent<TransformComponent>(100 , 875 , 75, 65 , 1);
    Player.addComponent<SpriteComponent>("Assets/Plane.png");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("Player");
    Boat.addComponent<TransformComponent>(200 , 100 , 230 , 60 , 1);
    Boat.addComponent<SpriteComponent>("Assets/Boat.png");
    Boat.addComponent<ColliderComponent>("wall");
    Fuel.addComponent<TransformComponent>(200 , 500);
    Fuel.addComponent<SpriteComponent>("Assets/Fuel.png");
    Chopter.addComponent<TransformComponent>(200 , 700);
    Chopter.addComponent<SpriteComponent>("Assets/Chopter.png");

    

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
    if(Collision::AABB(Player.getComponent<ColliderComponent>().collider,
    Boat.getComponent<ColliderComponent>().collider
    ))
    {
        std::cout<<"Wall hit"<<std::endl;
    }

    //std::cout<<Player.getComponent<TransformComponent>().pos.y<<std::endl;
    
    //Player.getComponent<TransformComponent>().pos.Add(Vector2D(1 , 1) );
    
    //destRect.x = newPlayer.getComponent<TransformComponent>().x();
    //destRect.y = newPlayer.getComponent<TransformComponent>().y();
   // std::cout<<player.getComponent<TransformComponent>()->pos.x<<endl;

}
void Game::Render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    
    Fuel.getComponent<SpriteComponent>().Draw();
    Chopter.getComponent<SpriteComponent>().Draw();
    Boat.getComponent<SpriteComponent>().Draw();
    Player.getComponent<SpriteComponent>().Draw();
    //SDL_DestroyTexture(Fuel.getComponent<SpriteComponent>().getTexture());
    
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
