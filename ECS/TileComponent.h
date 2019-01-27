// #pragma once
// #include "ECS.h"
// #include "TransformComponent.h"
// #include "SDL2/SDL.h"
// #include <iostream>
// class TileComponent : public Component
// {

// public:
//     TransformComponent* transform;
//     SpriteComponent* sprite;
//     SDL_Rect tileRect;
//     int TileID;
//     std::string stringid ;
//     TileComponent() = default;
//     TileComponent(int x , int y ,int w , int h , int id)
//     {
//         tileRect.x = x;
//         tileRect.y = y;
//         tileRect.w = w;
//         tileRect.h = h;
//         TileID = id;
//         switch(TileID){
//             case 0: 
//                 stringid = "water";
//             break;
//             case 1:
//                 stringid = "grass";
//             break;

//         }
//     }
//     void Init() override{
//         entity->addComponent<TransformComponent>(tileRect.x , tileRect.y , tileRect.w , tileRect.h , 1);
//         transform = &entity->getComponent<TransformComponent>();
//         entity->addComponent<SpriteComponent>(stringid);
//         sprite = &entity->getComponent<SpriteComponent>();
//     }

// };