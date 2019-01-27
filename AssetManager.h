#pragma once 
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL2/SDL_ttf.h"

class AssetManager
{
public:
AssetManager(Manager* man);
~AssetManager();

//gameobjects

void CreateProjectile(Vector2D pos , int range , int speed ,  std::string id , bool isPlayer);
void CreateEnemy( Vector2D pos , int speed ,  std::string id);
void CreateFriend( Vector2D pos ,int speed ,  std::string id);
void CreateWall( Vector2D pos ,int speed ,  std::string id);
	
//texute management
void AddTexture(std::string id , const char* path);
SDL_Texture* GetTexture(std::string id);
void AddFont(std::string id , const char* path , int size);
TTF_Font* GetFont(std::string id);
int canShoot;
private:
Manager* manager;
std::map<std::string,SDL_Texture*> textures;
std::map<std::string,TTF_Font*> fonts;
};
