#ifndef TERRAIN_H // include guard
#define TERRAIN_H
#include "FastNoise.h"
#include <curses.h>
#include <vector>
#include <time.h>
#include "settings.h"
#include "resource.h"
#include <string>
/* used to use the same noise generator to
   get different values at the "same" spot */
#define NOISE_GEN_OFFSET 9000
using namespace std;
class TileManager;
class Tile;
class TerrainTile;
class PlainsTile;
class BuildingTile;


// Abstract class for tiles

class Tile
{
  public:
    Tile();
    virtual chtype render();
    void setCharacter(chtype target);
    virtual string getToolText();
    void setText(string target);
    virtual void step() = 0;
    virtual double getHeight() const;
    virtual void setHeight(double target);
    virtual ~Tile();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
  protected:
    double height;
    chtype character;
    string description;
    int y_coord = 0;
    int x_coord = 0;

};
////////////////////////////////////////////////////////
class TerrainTile: public Tile
{
  public:
    TerrainTile(int y, int x);
    int getUsability();
    chtype render();
    string getToolText();
    virtual void step();
    void setBuilding(BuildingTile * tile);
  protected:
    int usability = 0;
    BuildingTile * building = nullptr;

};

enum BuildingType {BT_LumberMill = 1,
                   BT_Farm = 2};

inline BuildingType operator|(BuildingType A, BuildingType B){
  return static_cast<BuildingType>(static_cast<int>(A) | static_cast<int>(B));
}
class BuildingTile: public Tile
{
  public:
    BuildingTile(int y, int x);
    static chtype blob();
  protected:
    int buildTime = 0;

};
////////////////////////////////////////////////////////
class PlainsTile: public TerrainTile
{
  public:
    PlainsTile(int y, int x);


};
class ForestTile: public TerrainTile
{
  public:

    ForestTile(int y, int x);


};
class RiverTile: public TerrainTile
{
  public:
    RiverTile(int y, int x);

};
////////////////////////////////////////////
class LumberMill: public BuildingTile
{
  public:
    LumberMill(int y, int x);
    int calculateProduction(int acceptedUsage);
    string getToolText() ;
    virtual void step();
    void setProduction(int target);

  private:
    int production;

};
////////////////////////////////////////////////

class TileManager
{
  public:
    TileManager();
    void stepAll();
    void dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset);
    void createRivers(int chunkSize);
    void fillRiver(int y, int x);
    string getToolText(int y, int x);
    
    static void create(BuildingType bt, int y, int x);
    static vector<vector<TerrainTile* > > tileVector;

  private:
    vector<double (*)(double, double)> x;
    FastNoise noiseGen;
    double baseRiverProb = 3;
};


#endif
