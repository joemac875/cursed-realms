#include "map.h"
#include "manager.h"

void Map::shift(int direction){
  switch (direction){
    case 0:
      if (y_curs_off > 0){
      y_curs_off-=1;
      }
      break;
    case 1:
      if (x_curs_off + GAME_WIDTH < MAP_WIDTH){
        x_curs_off+=1;
      }
      break;
    case 2:
      if (y_curs_off + GAME_HEIGHT < MAP_HEIGHT){
        y_curs_off+=1;
      }
      break;
    case 3:
      if (x_curs_off > 0){
        x_curs_off-=1;
      }
      break;
  }
}
Map::Map(){
  terrainManager = TerrainManager();
  // Randomly pick a starting area in the map
  y_curs_off = rand() % (MAP_HEIGHT-GAME_HEIGHT);
  x_curs_off = rand() % (MAP_WIDTH-GAME_WIDTH);
}
void Map::dumpRenders(vector<vector<chtype> > &storage){
  terrainManager.dumpRenders(storage, y_curs_off, x_curs_off);
}
void Map::stepAll(){
  terrainManager.stepAll();
}
const char * Map::getToolText(int y,int x){
  y += y_curs_off;
  x += x_curs_off;
  return terrainManager.getToolText(y,x);
}