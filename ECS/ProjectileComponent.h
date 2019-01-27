#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"
class ProjectileComponenet : public Component
{

public:
ProjectileComponenet(int rng , int sp) : range(rng) , speed(sp)
{}
~ProjectileComponenet(){
    
}

void Init() override{

    transform = &entity->getComponent<TransformComponent>();

}
void Update() override
{
    
     if(transform->pos.y < 0 ||
            transform->pos.x < 0 ||
            transform->pos.x > 900 ||
            transform->pos.y > 1200
    )
        entity->Destroy();
    
}
void AIShoot(bool shoot)
{
    canShoot = shoot;
}
bool AICanShoot()
{
    return canShoot;
}
private:
    bool canShoot = false;
    TransformComponent* transform;
    int range = 0;
    int speed = 10;
    int distance = 0;

};