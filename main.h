#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window *MainWindow = nullptr;
SDL_Renderer *MainRenderer = nullptr;
SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer*);
void renderTexture(SDL_Texture*, SDL_Renderer* , int, int);