#ifndef BUILDING_H // include guard
#define BUILDING_H
#include <curses.h>
#include "settings.h"
#include "resource.h"
#include "terrain.h"
#include <vector>
#include <string>
class Building;
class BuildingManager;
using namespace std;
class BuildingManager{
  public:
    // Constructor for buidling manager
    template <class buildingType> void addBuilding(int y, int x){
      buildingVector[y][x] = (new buildingType(y,x));
    }
    BuildingManager();
    void dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset);
    void stepAll();
    string getToolText (int y, int x) const;
  private:
    vector<vector<Building*> > buildingVector;


};

class Building{
  public:
    /*
    Constructor for building class
    @param x and y are the map coordinates of the building
    */
    Building(int y, int x);
    Building();
    // game tick step function
    virtual void step() = 0;
    virtual string getToolText() = 0;
    int getX();
    int getY();
    const char * getDescription() const;
    chtype render();
    void setCharacter(chtype target);
    void setText(const char * target);
    int getProduction() const;
    void setProduction(int target);
    vector<TerrainTile*> neighbors;

  private:
    const char * text;
    chtype character;
    int x_coord;
    int y_coord;
    int production = 1;
};

class LumberMill: public Building
{
  public:
    LumberMill(int y, int x);
    int calculateProduction(int acceptedUsage);
    virtual string getToolText() ;

    virtual void step();

};
#endif
