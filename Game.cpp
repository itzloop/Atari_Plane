#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* playertexture;
SDL_Rect srcRect , destRect;
bool Game::isFired = false;
Manager manager;
std::vector<ColliderComponent*> Game::colliders;
AssetManager* Game::assets = new AssetManager(&manager);
auto& Player(manager.addEntity());
auto& Boat(manager.addEntity());
auto& Chopter(manager.addEntity());
auto& Fuel(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
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
        SDL_SetRenderDrawColor(renderer,255 , 255 , 255 , 255);
    }
    else{
        isRunning = false;
    }
    assets->AddTexture("Player" , "Assets/Plane.png");
    assets->AddTexture("Boat" , "Assets/Boat.png");
    assets->AddTexture("Fuel" , "Assets/Fuel.png");
    assets->AddTexture("Chopter" , "Assets/Chopter.png");
    assets->AddTexture("left_plane" , "Assets/left_plane.png");
    assets->AddTexture("right_plane" , "Assets/right_plane.png");
    assets->AddTexture("grass" , "Assets/grass.png");
    assets->AddTexture("water" , "Assets/water.png");
    map = new Map();
    tile0.addComponent<TileComponent>(200 , 200 , 32 , 32 , 0);
    tile1.addComponent<TileComponent>(250 , 250 , 32 , 32 , 1);
    tile1.addComponent<ColliderComponent>("grass");
    Player.addComponent<TransformComponent>(100 , 875 , 75, 65 , 1);
    Player.addComponent<SpriteComponent>("Player");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("Player");
    Boat.addComponent<TransformComponent>(200 , 100 , 230 , 60 , 1);
    Boat.addComponent<SpriteComponent>("Boat");
    Boat.addComponent<ColliderComponent>("Boat");
    Fuel.addComponent<TransformComponent>(200 , 500 , 80 , 150 ,1);
    Fuel.addComponent<SpriteComponent>("Fuel");
    Fuel.addComponent<ColliderComponent>("Fuel");
    Chopter.addComponent<TransformComponent>(200 , 700 , 115 , 70 , 1);
    Chopter.addComponent<SpriteComponent>("Chopter");
    Chopter.addComponent<ColliderComponent>("Chopter");

    

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
    for(auto cc : colliders)
    {
        if(cc->tag != "Player")
        {
            Collision::AABB(Player.getComponent<ColliderComponent>(),*cc);
        }
   
    }
}
void Game::Render(){
    SDL_RenderClear(renderer);
    manager.Draw();
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

void Game::AddTile(int id , int x , int y)
{

}