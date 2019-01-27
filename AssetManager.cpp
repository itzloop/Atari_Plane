#include "AssetManager.h"
#include "ECS/Components.h"
#include <ctime>
AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{
}


void AssetManager::CreateProjectile( Vector2D pos , int range , int speed ,  std::string id , bool isPlayer){
	auto&  projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x - 7.5 , pos.y , 15 , 30 , 1);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponenet>(range , speed);
	if(canShoot)
		projectile.getComponent<TransformComponent>().velocity.y = 1;
	else
		projectile.getComponent<TransformComponent>().velocity.y = -1;
	if(isPlayer)
		projectile.getComponent<TransformComponent>().velocity.y = -1;

	projectile.getComponent<TransformComponent>().speed = speed;
	
	projectile.addComponent<ColliderComponent>(id);
	if(isPlayer)
		projectile.AddGroup(Game::groupProjectiles);
	else
		projectile.AddGroup(Game::groupEnemyProjectiles);

	
}
void AssetManager::CreateEnemy( Vector2D pos , int speed , std::string id){
	srand(time(0));
	int RandomX = rand()%300 + 400;
	int moveX = rand()%1000;
	canShoot = rand()%1000;
	if(moveX <= 800)
		moveX = 0;
	if(canShoot <=800)
		canShoot = 0; 
	
	if(id == "LBoat" || id == "RBoat")
	{
		auto& Boat(manager->addEntity());
		Boat.addComponent<TransformComponent>(RandomX , pos.y , 200 , 50 , 1);
		Boat.getComponent<TransformComponent>().velocity.y = 1;
		if(moveX)
			Boat.getComponent<TransformComponent>().velocity.x = 1;
		if(canShoot)
			Boat.getComponent<TransformComponent>().AICanShoot = true;
		Boat.getComponent<TransformComponent>().speed = speed;
    	Boat.addComponent<SpriteComponent>(id);
    	Boat.addComponent<ColliderComponent>("Boat");
    	Boat.AddGroup(Game::groupEnemies);
	}
	if(id == "LChopter" || id=="RChopter")
	{
		auto& Chopter(manager->addEntity());
		Chopter.addComponent<TransformComponent>(pos.x , pos.y , 115 , 70 , 1);
		Chopter.getComponent<TransformComponent>().velocity.y = 1;
		if(moveX)
			Chopter.getComponent<TransformComponent>().velocity.x = 1;
		if(canShoot)
			Chopter.getComponent<TransformComponent>().AICanShoot = true;
		
		Chopter.getComponent<TransformComponent>().speed = speed;
		Chopter.addComponent<SpriteComponent>(id);
		Chopter.addComponent<ColliderComponent>("Chopter");
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
		Fuel.getComponent<TransformComponent>().speed = speed;

    	Fuel.addComponent<SpriteComponent>(id);
    	Fuel.addComponent<ColliderComponent>(id);
    	Fuel.AddGroup(Game::groupFriend);
		std::cout<<"Fuel Created"<<std::endl;

	}
}



void AssetManager::CreateWall(Vector2D pos  , int speed ,  std::string id)
{
	srand(time(0));
	int randomX = rand()%1000;
	int x;
	
	
	if(randomX>=900)
		randomX = 50;
	else if(randomX <= 500)
		randomX = 150;
	else
		randomX = 100;
	//std::cout<<randomX<<std::endl;
	
	auto& Wall(manager->addEntity());
	if(pos.x > 500)
	{
		Wall.addComponent<TransformComponent>(pos.x-300+randomX,  pos.y, 300 , 400 , 1);
		Wall.addComponent<SpriteComponent>("RWall");
	}
	else
	{
		Wall.addComponent<TransformComponent>(pos.x -randomX,  pos.y, 300 , 400 , 1);
		Wall.addComponent<SpriteComponent>("LWall");

	}
	
	Wall.getComponent<TransformComponent>().velocity.y = 1;
	Wall.getComponent<TransformComponent>().speed = speed;
	
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


void AssetManager::AddFont(std::string id , const char* path , int size){
	fonts.emplace(id , TTF_OpenFont(path, size));
}
TTF_Font* AssetManager::GetFont(std::string id){
	return fonts[id];
}