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
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    void setTexture(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void Init() override{
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void Update() override{
        destRect.x = (int)transform->pos.x;
        destRect.y = (int)transform->pos.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }
    SDL_Texture* getTexture()
    {
        return texture;
    }
    void DestroyTexture()
    {   
        texture = nullptr;
    }


    void Draw() override{
        TextureManager::Draw(texture ,  NULL, &destRect);
    }



};


