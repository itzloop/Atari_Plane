#pragma once
#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:

    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect , destRect;

public:

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
    }
    void setTexture(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void Init() override{
        transform = &entity->getComponent<TransformComponent>();
        destRect.w = destRect.h = 45;
    }

    void Update() override{
        destRect.x = transform->pos.x;
        destRect.y = transform->pos.y;
    }

    void Draw() override{
        TextureManager::Draw(texture ,  NULL, &destRect);
    }



};


