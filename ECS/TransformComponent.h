#pragma once
#include "Components.h"
#include "../Vector2D.h"


class TransformComponent : public Component
{

private:


public:
    bool enteredScreen = false;
    int height = 400;
    int width = 200;
    int scale = 1;
    Vector2D pos; 
    Vector2D velocity;
    int speed = 8;
    bool AICanShoot = false;
    TransformComponent(){
        pos.Zero();
        velocity.Zero();
       
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
       pos.Zero();
        scale = sc; 
    }
    
    void Init() override{
       velocity.Zero();
    }

    void Update() override
    {
        if(AICanShoot)
            velocity.y = 1;
        if(velocity.x == 1 ) 
        {
            
            if(pos.x <= 780)
                pos.x += velocity.x * speed;
          
                
        }
        else if(velocity.x == -1)
        {
            if(pos.x >= 0)
                pos.x += velocity.x * speed;
        }
        pos.y += velocity.y * speed;
    }

};