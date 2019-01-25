#include "AssetManager.h"
#include "ECS/Components.h"
AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{
}


void AssetManager::CreateProjectile(Vector2D pos , int range , int speed ,  std::string id){
	auto&  projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x , pos.y , 15 , 45 , 1);
	projectile.addComponent<SpriteComponent>("Projectile");
	projectile.addComponent<ProjectileComponenet>(range , speed);
	projectile.addComponent<ColliderComponent>("Projectile");

}
void AssetManager::AddTexture(std::string id , const char* path)
{
	textures.emplace(id,TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id){
	return textures[id];
}