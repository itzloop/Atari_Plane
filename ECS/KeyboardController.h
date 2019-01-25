#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
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
                    sprite->setTexture("Assets/left_plane.png");
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 1;
                    sprite->setTexture("Assets/right_plane.png");
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 1;
                    break;
                case SDLK_SPACE:;
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
                    sprite->setTexture("Assets/Plane.png");
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 0;
                    sprite->setTexture("Assets/Plane.png");
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 0;
                    break;
                }
        }
    }




};