#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Components.h"
class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    TransformComponent* transform;
    ColliderComponent(std::string name)
    {
        tag = name;
    }
    void Init() override
    {
        if(!entity->HasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void Update() override
    {
        collider.x = static_cast<int>(transform->pos.x);
        collider.y = static_cast<int>(transform->pos.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }


};