#pragma once
#include "Game.h"

class Map
{

public:
    Map();
    ~Map();
    void LoadMap(int arr[][50]);
    void DrawMap();
    void shift(int arr[][50]);

private:
    SDL_Rect src , dest;
    SDL_Texture* grass;
    SDL_Texture* water;
    int map[60][50];
};