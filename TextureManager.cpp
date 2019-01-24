
#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* imagename){

SDL_Surface* tempSurface = IMG_Load(imagename);
SDL_Texture* texure = SDL_CreateTextureFromSurface(Game::renderer , tempSurface);
SDL_FreeSurface(tempSurface);
return texure;

}

void TextureManager::Draw(SDL_Texture* texture , SDL_Rect* src , SDL_Rect* dest){

    SDL_RenderCopy(Game::renderer , texture , src , dest);
}