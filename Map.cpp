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
            if(tile == '\n')
            {
                    Game::AddTile(1 , x*20 , y*20);
                    mapfile.write(&tile , 1);              
            } 
            else
            {
                Game::AddTile(atoi(&tile) , x*20 , y*20);
                mapfile.ignore(2,',');
            }
            
           
        }
       
    }

    
    mapfile.close();

}



