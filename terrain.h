#ifndef TERRAIN_H // include guard
#define TERRAIN_H
#include "FastNoise.h"
#include <curses.h>
#include <vector>
#include <time.h>
#define MAP_WIDTH  40
#define MAP_HEIGHT 30
/* used to use the same noise generator to
   get different values at the "same" spot */
#define NOISE_GEN_OFFSET 9000
using namespace std;
class TerrainManager;
class TerrainTile;
class PlainsTile;

class TerrainManager
{
  public:
    TerrainManager();
    void stepAll();
    void dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset);
    void createRivers(int chunkSize);
    void fillRiver(int y, int x);
    const char * getToolText(int y, int x);

  private:
    vector<vector<TerrainTile*> > tileVector;
    FastNoise noiseGen;


    double baseRiverProb = 3;
};
// Abstract class for terrain tiles
class TerrainTile
{
  public:
    chtype render();
    void setCharacter(chtype target);
    void setHeight(double target);
    const char * getToolText() const;
    void setText(const char * target);
    double getHeight() const;
    virtual void step() = 0;
    virtual ~TerrainTile();
  protected:
    chtype character;
    double height;
    const char * text;
};
class PlainsTile: public TerrainTile
{
  public:
    PlainsTile();
    virtual void step();

};
class ForestTile: public TerrainTile
{
  public:
    ForestTile();
    virtual void step();

};
class RiverTile: public TerrainTile
{
  public:
    RiverTile();
    virtual void step();

};


#endif
