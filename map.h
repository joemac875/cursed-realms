#ifndef MAP_H
#define MAP_H
#include <curses.h>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>
#include "FastNoise.h"
#include "tile.h"

class MapOption;
class Map
{
  public:
    Map();
    void dumpRenders(vector<vector<chtype> > &storage);
    void stepAll();
    void shift(int direction);
    string getToolText(int y,int x);
    TileManager getTileManager();
    BuildingType getAcceptedBuildings(int y_curs, int x_curs);
    int get_x_curs_off();
    int get_y_curs_off();
  private:
    TileManager terrainManager;
    int x_curs_off;
    int y_curs_off;
};



#endif
