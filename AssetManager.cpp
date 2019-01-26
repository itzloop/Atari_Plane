#include "AssetManager.h"
#include "ECS/Components.h"
#include <ctime>
AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{
}


void AssetManager::CreateProjectile( Vector2D pos , int range , int speed ,  std::string id){
	auto&  projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x , pos.y , 15 , 30 , 1);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponenet>(range , speed);
	projectile.getComponent<TransformComponent>().velocity.y = -1;
	projectile.getComponent<TransformComponent>().speed = speed;
	
	projectile.addComponent<ColliderComponent>(id);
	projectile.AddGroup(Game::groupProjectiles);
}
void AssetManager::CreateEnemy( Vector2D pos , int speed , std::string id){
	
	if(id == "Boat")
	{
		auto& Boat(manager->addEntity());
		Boat.addComponent<TransformComponent>(pos.x , pos.y , 230 , 60 , 1);
		Boat.getComponent<TransformComponent>().velocity.y = 1;

    	Boat.addComponent<SpriteComponent>(id);
    	Boat.addComponent<ColliderComponent>(id);
    	Boat.AddGroup(Game::groupEnemies);
	}
	if(id == "Chopter")
	{
		auto& Chopter(manager->addEntity());
		Chopter.addComponent<TransformComponent>(pos.x , pos.y , 115 , 70 , 1);
		Chopter.getComponent<TransformComponent>().velocity.y = 1;
		Chopter.addComponent<SpriteComponent>(id);
		Chopter.addComponent<ColliderComponent>(id);
		Chopter.AddGroup(Game::groupEnemies);
		std::cout<<"Chopter Created"<<std::endl;
	}
	 
}
void AssetManager::CreateFriend( Vector2D pos  , int speed ,  std::string id){
	if(id == "Fuel")
	{
		auto& Fuel(manager->addEntity());
		Fuel.addComponent<TransformComponent>(pos.x , pos.y , 80 , 150 ,1);
		Fuel.getComponent<TransformComponent>().velocity.y = 1;
		Fuel.getComponent<TransformComponent>().velocity.x = 0;

    	Fuel.addComponent<SpriteComponent>(id);
    	Fuel.addComponent<ColliderComponent>(id);
    	Fuel.AddGroup(Game::groupFriend);
	}
}



void AssetManager::CreateWall(Vector2D pos  , int speed ,  std::string id)
{
	srand(time(0));
	int randomW = rand()%1000;
	int x;
	
	
	if(randomW>=700)
		randomW = 300;
	else
		randomW = 100;
	//std::cout<<randomX<<std::endl;
	
	
	auto& Wall(manager->addEntity());
	Wall.addComponent<TransformComponent>(pos.x,  pos.y, randomW , 400 , 1);
	Wall.getComponent<TransformComponent>().velocity.y = 1;
	Wall.getComponent<TransformComponent>().speed = speed;
	Wall.addComponent<SpriteComponent>(id);
	Wall.addComponent<ColliderComponent>(id);
	Wall.AddGroup(Game::groupWall);
}
void AssetManager::AddTexture(std::string id , const char* path)
{
	textures.emplace(id,TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id){
	return textures[id];
}