#pragma once
#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
class SpriteComponent : public Component
{
private:

    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect , destRect;

public:

    SpriteComponent() = default;
    SpriteComponent(std::string id)
    {
        setTexture(id);
    }
    ~SpriteComponent()
    {
        
    }
    void setTexture(std::string id)
    {
        texture = Game::assets->GetTexture(id);
    }

    void Init() override{
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void Update() override{
        destRect.x = static_cast<int>(transform->pos.x);
        destRect.y = static_cast<int>(transform->pos.y);
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


