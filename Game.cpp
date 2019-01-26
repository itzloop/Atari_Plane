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
// auto& Boat(manager.addEntity());
// auto& Chopter(manager.addEntity());
// auto& Fuel(manager.addEntity());

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
        SDL_SetRenderDrawColor(renderer,45 , 50 , 184 , 255);
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
    assets->AddTexture("Projectile" , "Assets/Missile.png");
    assets->AddTexture("Wall" , "Assets/Wall.png");
    map = new Map();
    Map::LoadMap("map30*40.txt" , 30 , 40);
    Player.addComponent<TransformComponent>(100 , 875 , 75, 65 , 1);
    Player.addComponent<SpriteComponent>("Player");
    Player.addComponent<KeyboardController>(&manager);
    Player.addComponent<ColliderComponent>("Player");
    Player.AddGroup(groupPlayers);
    assets->CreateEnemy(Vector2D(200 , 100) , 2 ,"Boat");
    assets->CreateFriend(Vector2D(200 , 50) , 2 , "Fuel");
    assets->CreateEnemy(Vector2D(200 , 500) , 2 ,"Chopter");
    assets->CreateEnemy(Vector2D(400 , 500) , 2 ,"Chopter");
    assets->CreateWall(Vector2D(0 , -400) , 5 , "Wall");

    
    

}
void Game::HandleEvents(){
    
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT: isRunning = false;
            break;
    }
}
auto& Players(manager.GetGroup(Game::groupPlayers));
auto& Enemies(manager.GetGroup(Game::groupEnemies));
auto& Projectiles(manager.GetGroup(Game::groupProjectiles));
auto& Friends(manager.GetGroup(Game::groupFriend));
auto& Walls(manager.GetGroup(Game::groupWall));
void Game::Update(){
    // destRect.h = 60;
    // destRect.w = 75;
    manager.refresh();
    manager.Update();
     //std::cout<<fuel<<std::endl;
       for(auto& w : Walls)
       {
           if(w->getComponent<TransformComponent>().pos.y > 1200)
           {
               assets->CreateWall(Vector2D(0 , 0) , 5 , "Chopter");
              w->Destroy();
               
           }
           if(w->getComponent<TransformComponent>().pos.y > 1200);
                
       }
    for(auto& e : Enemies)
    {
            for(auto& p : Projectiles)
            {
                if(Collision::AABB(e->getComponent<ColliderComponent>().collider , 
                p->getComponent<ColliderComponent>().collider))
                {
                    p->Destroy();
                    e->Destroy();
                }
            }
        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
        e->getComponent<ColliderComponent>().collider))
        {
           e->Destroy();
           Health--;
           if(Health <= 0)
            isRunning = false;
           std::cout<<Health<<std::endl;

        }
    }
    for(auto& f : Friends)
    {

            for(auto& p : Projectiles)
            {
                if(Collision::AABB(f->getComponent<ColliderComponent>().collider , 
                p->getComponent<ColliderComponent>().collider))
                {
                    p->Destroy();
                    f->Destroy();
                }
            }
           

        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
        f->getComponent<ColliderComponent>().collider))
        { 
            if(fuel < 100)
                fuel+= 0.5;

        }
    }
     fuel-=0.3;
       for(auto& w: Walls)
            {
                if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
                w->getComponent<ColliderComponent>().collider))
                {
                    w->Destroy();
                    
                }
            }
    //Boat.getComponent<TransformComponent>().pos.y +=5;
}

void Game::Render(){
    SDL_RenderClear(renderer);
    for(auto& w : Walls)
        w->Draw();
     for(auto& e : Enemies)
        e->Draw();
    for(auto& f : Friends)
    f->Draw();
    for(auto& p : Players)
        p->Draw();
    for(auto& proj : Projectiles)
        proj->Draw();
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
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,30,30 , id);
}