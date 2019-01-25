#pragma once
#include "Components.h"
#include "../Vector2D.h"


class TransformComponent : public Component
{

private:


public:
    int height = 32;
    int width = 32;
    int scale = 1;
    Vector2D pos; 
    Vector2D velocity;
    int speed = 5;
    TransformComponent(){
        pos.x = 0.0f;
        pos.y = 0.0f;
       
   }
    TransformComponent(float x , float y){
        pos.x = x;
        pos.y = y;
    }
      TransformComponent(float x , float y , int w , int h , int sc){
        pos.x = x;
        pos.y = y;
        height = h;
        width = w;
        scale = sc; 
    }

    
      TransformComponent(int sc){
        pos.x = 0;
        pos.y = 0;
        scale = sc; 
    }
    
    void Init() override{
        velocity.x = 0;
        velocity.y = 0;
    }

    void Update() override
    {
        if(velocity.x == 1 ) 
        {
            if(pos.x <= 1150)
                pos.x += velocity.x * speed;
        }
        else
        {
            if(pos.x >= 0)
                pos.x += velocity.x * speed;
        }

        
       

        pos.y += velocity.y * speed;
    }

};