#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* playertexture= nullptr;
TTF_Font* font;
SDL_Color textColor = {255 , 255 , 255 , 255};
SDL_Rect srcRect , destRect;
bool Game::isFired = false;
Manager manager;
std::vector<ColliderComponent*> Game::colliders;
AssetManager* Game::assets = new AssetManager(&manager);
auto& Player(manager.addEntity());
auto& Health(manager.addEntity());
auto& Fuel(manager.addEntity());
auto& Score(manager.addEntity());
auto& EnemiesKilled(manager.addEntity());
auto& Highscore(manager.addEntity());


SDL_Event Game::event;

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
        if(TTF_Init() < 0)
            std::cout<<"TTF FAILED"<<std::endl;
        font = TTF_OpenFont("Assets/font.ttf",18);

    }
    else{
        isRunning = false;
    }
    if(TTF_Init() == -1)
    {
        std::cout<<"Err TTF"<<std::endl;
    }
    assets->AddFont("font" , "Assets/font.ttf" , 16);
    assets->AddTexture("Player" , "Assets/Plane.png");
    assets->AddTexture("LBoat" , "Assets/Boat_Left.png");
    assets->AddTexture("RBoat" , "Assets/Boat_Right.png");
    assets->AddTexture("Fuel" , "Assets/Fuel.png");
    assets->AddTexture("LChopter" , "Assets/Chopter_Left.png");
    assets->AddTexture("RChopter" , "Assets/Right.png");
    assets->AddTexture("left_plane" , "Assets/left_plane.png");
    assets->AddTexture("right_plane" , "Assets/right_plane.png");
    assets->AddTexture("grass" , "Assets/grass.png");
    assets->AddTexture("water" , "Assets/water.png");
    assets->AddTexture("Projectile" , "Assets/Missile.png");
    assets->AddTexture("LWall" , "Assets/Wall_Left.png");
    assets->AddTexture("RWall" , "Assets/Wall_Right.png");
    Player.addComponent<TransformComponent>(375 , 875 , 75, 65 , 1);
    Player.addComponent<SpriteComponent>("Player");
    Player.addComponent<KeyboardController>(&manager);
    Player.addComponent<ColliderComponent>("Player");
    Player.AddGroup(groupPlayers);
    Health.addComponent<UILabel>(10 , 10 , "TEST" , "font" , textColor );
    Fuel.addComponent<UILabel>(10 , 40 , "TEST" , "font" , textColor );
    Score.addComponent<UILabel>(10 , 70 , "TEST" , "font" , textColor );
    Highscore.addComponent<UILabel>(10 , 100 , "TEST" , "font" , textColor );
    EnemiesKilled.addComponent<UILabel>(10 , 130 , "TEST" , "font" , textColor );
    
    
    assets->CreateEnemy(Vector2D(300, 100) , speed ,"RBoat");
    assets->CreateFriend(Vector2D(200 , 50) , speed , "Fuel");
    assets->CreateEnemy(Vector2D(300 , 500) , speed ,"LChopter");
    //Creating the first walls
    assets->CreateWall(Vector2D(0 , -800) , speed , "LWall");
    assets->CreateWall(Vector2D(0 ,  -400) , speed , "LWall");
    assets->CreateWall(Vector2D(0 , 0) , speed , "LWall");
    assets->CreateWall(Vector2D(0 ,400) , speed , "LWall");
    assets->CreateWall(Vector2D(0 , 800) , speed , "LWall");
    assets->CreateWall(Vector2D(900 , -800) , speed , "RWall");
    assets->CreateWall(Vector2D(900 ,  -400) , speed , "RWall");
    assets->CreateWall(Vector2D(900 , 0) , speed , "RWall");
    assets->CreateWall(Vector2D(900 ,400) , speed , "RWall");
    assets->CreateWall(Vector2D(900 , 800) , speed , "RWall");

    
    

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
auto& EnemyProjectiles(manager.GetGroup(Game::groupEnemyProjectiles));
auto& Friends(manager.GetGroup(Game::groupFriend));
auto& Walls(manager.GetGroup(Game::groupWall));



void Game::Update(){
    // destRect.h = 60;
    // destRect.w = 75;
    std::stringstream ss;
    ss << "Health: " << health ;
    Health.getComponent<UILabel>().SetLabelText(ss.str() , "font");
    ss <<"Fuel: "<<fuel;
    Fuel.getComponent<UILabel>().SetLabelText(ss.str() , "font");
    ss <<"Enemies Killed: "<<fuel;
    Fuel.getComponent<UILabel>().SetLabelText(ss.str() , "font");
    ss <<"Score: "<<score;
    Fuel.getComponent<UILabel>().SetLabelText(ss.str() , "font");
    ss <<"HighScore: "<<highScore;
    Fuel.getComponent<UILabel>().SetLabelText(ss.str() , "font");
    manager.refresh();
    manager.Update();
     //std::cout<<manager.GetGroup(groupWall).size()<<std::endl;
     speedMultiplier+=0.00001;
     speed+=speedMultiplier;
     if(manager.GetGroup(groupWall).size() <8)
     {
         assets->CreateWall(Vector2D(0 , -390) , speed , "LWall");
         assets->CreateWall(Vector2D(900, -390) , speed , "RWall");
     }
    for(auto& p : EnemyProjectiles)
    {
        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
        p->getComponent<ColliderComponent>().collider))
        {
            isRunning = false;
        }
    }
    if(manager.GetGroup(groupEnemies).size()< 5)
    {
        assets->CreateEnemy(Vector2D(300,   -50) , speed ,"RBoat");
        assets->CreateEnemy(Vector2D(300 , -500) , speed ,"LChopter");
    }
    if(manager.GetGroup(groupFriend).size() < 2)
    {

        assets->CreateFriend(Vector2D(200 , -300) , speed , "Fuel");
    }
    for(auto& w : Walls)
    {
        w->getComponent<TransformComponent>().speed = speed;
        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
        w->getComponent<ColliderComponent>().collider))
        {
            isRunning = false;
        }
            
        for(auto& e : Enemies)
        {
            if(Collision::AABB(w->getComponent<ColliderComponent>().collider,
            e->getComponent<ColliderComponent>().collider))
            {
                e->getComponent<TransformComponent>().velocity.x *= -1;
            }
        }
        //destroy walls at the end of screen
        if(w->getComponent<TransformComponent>().pos.y > 1200)
            w->Destroy();
            
    }

    for(auto& e : Enemies)
    {

        e->getComponent<TransformComponent>().speed = speed;
        if(e->getComponent<TransformComponent>().velocity.x == -1 && e->getComponent<ColliderComponent>().tag == "Boat")
        {
            e->getComponent<SpriteComponent>().setTexture("LBoat");
        }
        else if(e->getComponent<TransformComponent>().velocity.x == 1 && e->getComponent<ColliderComponent>().tag == "Boat")
        {
            e->getComponent<SpriteComponent>().setTexture("RBoat");
        }
        else if(e->getComponent<TransformComponent>().velocity.x == -1)
        {
            e->getComponent<SpriteComponent>().setTexture("LChopter");
        }
        
        //projectile hiting enemies
        if(e->getComponent<TransformComponent>().AICanShoot)
        {
            
            if(manager.GetGroup(groupEnemyProjectiles).size() < 3)
            {
                assets->CreateProjectile(e->getComponent<TransformComponent>().pos,300,10, "Projectile" ,false);
            }
        }
    
        
        for(auto& p : Projectiles)
        {
            if(Collision::AABB(e->getComponent<ColliderComponent>().collider , 
            p->getComponent<ColliderComponent>().collider))
            {
                p->Destroy();
                e->Destroy();
                
            }
        }
        
        //Collision between Player and enemies
        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider , 
        e->getComponent<ColliderComponent>().collider))
        {
           e->Destroy();
           health--;
           if(health <= 0)
            isRunning = false;
           std::cout<<health<<std::endl;

        }
    }
    for(auto& f : Friends)
    {   

        f->getComponent<TransformComponent>().speed = speed;

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
     fuel-=0.05;
    
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
    for(auto& proj : EnemyProjectiles)
    proj->Draw();
    Health.Draw();
    Fuel.Draw();
    Score.Draw();
    Highscore.Draw();
    EnemiesKilled.Draw();
    SDL_RenderPresent(renderer);
}
void Game::Clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
bool Game::Running(){
    return isRunning;
}

