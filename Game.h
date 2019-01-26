#ifndef Game_h
#define Game_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
class ColliderComponent;
class AssetManager;

class Game{

public:
    Game();
    ~Game();
    void Init(const char* title , int x , int y , int width , int height , bool isFullScreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool Running();
    static void AddTile(int id , int x , int y);
    static SDL_Renderer* renderer;
    static AssetManager* assets;
    static SDL_Event event;
    static bool isFired;
    enum groupLabrls : std::size_t
{
    groupWall,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupFriend,
    groupProjectiles
};

    static std::vector<ColliderComponent*> colliders;
private:
    bool isRunning;
    SDL_Window* window;
    int count;
    int Health = 5;
    float fuel = 100.f;
    
};

#endif