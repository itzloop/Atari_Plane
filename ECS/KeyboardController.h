#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"

class KeyboardController : public Component
{
private:
Manager* manager;
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    KeyboardController(Manager* man) : manager(man)
    {

    }
    void Init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();

    }

    void Update() override
    {
        if(Game::event.type == SDL_KEYDOWN)
        {
            switch(Game::event.key.keysym.sym)
                {
                case SDLK_UP:
                    transform->velocity.y = -1;
                    break;
                case SDLK_LEFT:
                    transform->velocity.x = -1;
                    sprite->setTexture("left_plane");
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 1;
                    sprite->setTexture("right_plane");
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 1;
                    break;
                case SDLK_SPACE:
                if(manager->GetGroup(Game::groupProjectiles).size() < 2)
                Game::assets->CreateProjectile(Vector2D(transform->pos.x + transform->width/2,transform->pos.y),300,30 , "Projectile" ,true);
                
                break;
                }
        }

        if(Game::event.type == SDL_KEYUP)
        {
             switch(Game::event.key.keysym.sym)
                {
                case SDLK_UP:
                    transform->velocity.y = 0;
                    break;
                case SDLK_LEFT:
                    transform->velocity.x = 0;
                    sprite->setTexture("Player");
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 0;
                    sprite->setTexture("Player");
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 0;
                    break;
                }
        }
    }




};