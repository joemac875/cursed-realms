#ifndef BUILDING_H // include guard
#define BUILDING_H
#include <curses.h>
#include "settings.h"

#include <vector>
class Building;
class BuildingManager;
using namespace std;
class BuildingManager{
  public:
    // Constructor for buidling manager
    BuildingManager();
    void dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset);
    const char * getToolText (int y, int x) const;
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
    int getX();
    int getY();
    const char * getToolText() const;
    chtype render();
    void setCharacter(chtype target);
    void setText(const char * target);
  private:
    const char * text;
    chtype character;
    int x_coord;
    int y_coord;
};

class LumberMill: public Building
{
  public:
    LumberMill(int y, int x);
    virtual void step();

};
#endif
