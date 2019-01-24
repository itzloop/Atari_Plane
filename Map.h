#pragma once
#include "Game.h"

class Map
{

public:
    Map();
    ~Map();
    void LoadMap(int lvl[][50]);
    void DrawMap();


private:
    SDL_Rect src , dest;
    SDL_Texture* grass;
    SDL_Texture* water;
    int map[60][50];
};