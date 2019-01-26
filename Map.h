#pragma once
#include <string>

class Map
{

public:
    Map();
    ~Map();
    static void LoadMap(std::string path , int sizex , int sizey);
    void shift(int arr[][30]);

private:

};