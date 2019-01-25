#ifndef Game_h
#define Game_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isFired;
private:
    bool isRunning;
    SDL_Window* window;
    int count;
    
};

#endif