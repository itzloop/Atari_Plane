#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map(){
}
Map::~Map()
{
}
void Map::LoadMap(std::string path , int sizex , int sizey)
{
    char tile;
    std::fstream mapfile;

    mapfile.open(path);
    
    for(int y = 0 ; y < sizey ;y++ )
    {
        for(int x = 0 ; x < sizex ; x++)
        {
            mapfile.get(tile);
            
            if(x == 0)
            {
                Game::AddTile(1 , x*30 , y*30);   
                 mapfile.ignore(2,',');          
            } 
            else
            {
               // Game::AddTile(atoi(&tile) , x*30 , y*30);
                mapfile.ignore(2,',');
            }
            
           
        }
       //std::cout<<std::endl;
    }

    
    mapfile.close();

}



