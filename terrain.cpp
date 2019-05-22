#include "terrain.h"


vector<vector<TerrainTile*> > TerrainManager::tileVector;

TerrainManager::TerrainManager(){
  noiseGen.SetNoiseType(FastNoise::Simplex);
  noiseGen.SetFrequency(.125);
  noiseGen.SetSeed(time(NULL));
  for (int i = 0; i < MAP_HEIGHT; i++){
    vector<TerrainTile*> temp(MAP_WIDTH);
    for (int j = 0; j < MAP_WIDTH; j++){
        double x = noiseGen.GetNoise(i,j);
        if (x < 0.0) temp[j] = new PlainsTile();
        else temp[j] = new ForestTile();
        // Set the height of the tile to be something random
        noiseGen.SetFrequency(.05);
        temp[j]->setHeight(noiseGen.GetNoise(i,j));
        noiseGen.SetFrequency(.15);
    }
    tileVector.push_back(temp);
  }
  createRivers(10);
}
void TerrainManager::createRivers(int chunkSize){
  // go through in chunks of
  for (int i = chunkSize / 2; i < MAP_HEIGHT; i += chunkSize){
    for (int j = chunkSize / 2; j < MAP_WIDTH; j += chunkSize){
        // higher places have a higher chance of getting a river
        double augRiverProg  = baseRiverProb * tileVector[i][j]->getHeight();
        double roll = ((double) rand() / (RAND_MAX));
        if (roll < augRiverProg){
          delete tileVector[i][j];
          tileVector[i][j] = new RiverTile();
          fillRiver(i, j);
        }
    }
  }
}
void TerrainManager::fillRiver(int y, int x){
  //base case for at edge of map
  if ((y == MAP_HEIGHT-1) || (y == 0) || (x == 0) || (x == MAP_WIDTH-1)) return;
  int min_y = y;
  int min_x = x;
  double min_height = tileVector[y][x]->getHeight();
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
        if (tileVector[y + i][x + j]->getHeight() < min_height){
          min_y = y + i;
          min_x = x + j;
          min_height = tileVector[min_y][min_x]->getHeight();
        }
    }
  }
  // base case for nothing lower
  if ((min_y == y) && (min_x == x)) return;
  delete tileVector[min_y][min_x];
  tileVector[min_y][min_x] = new RiverTile();
  fillRiver(min_y, min_x);
}

void TerrainManager::dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset){
  for (int i = 0; i < storage.size(); i++){
    for (int j = 0; j < storage[i].size(); j++){
        storage[i][j] = tileVector[i+y_offset][j+x_offset]->render();
    }
  }
}

void TerrainManager::stepAll(){
  for (int i = 0; i < MAP_HEIGHT; i++){
    for (int j = 0; j < MAP_WIDTH; j++){
        tileVector[i][j]->step();
    }
  }
}
vector<TerrainTile*> TerrainManager::getNeighbors(int y, int x){
  vector<TerrainTile*> neighbors;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if ((i != 0) || (j != 0)) neighbors.push_back(tileVector[i][j]);
    }
  }
  return neighbors;
}
const char * TerrainManager::getToolText(int y, int x){
  return tileVector[y][x]->getToolText();
}
//ToDo - Implement destructor for terrain manager
chtype TerrainTile::render(){
  return character;
}

TerrainTile::~TerrainTile(){
}
int TerrainTile::getUsability(){
  return usability;
}

void TerrainTile::setCharacter(chtype target){
  character = target;
}
void TerrainTile::setHeight(double target){
  height = target;
}
void TerrainTile::setText(const char * target){
  text  = target;
}
double TerrainTile::getHeight() const {
  return height;
}
const char * TerrainTile::getToolText() const {
  return text;
}
void PlainsTile::step(){
  return;
}
PlainsTile::PlainsTile(){
  setText("Plains\n----\nA wholly uninspiring terrain tile.");
  setCharacter(' ');
}
void ForestTile::step(){
  return;
}
ForestTile::ForestTile(){
  usability = ResourceManager::WOOD;
  setText("Forest\n----\nLush trees veil the ultimate resource.");
  setCharacter(ACS_DIAMOND | COLOR_PAIR(1));
}

void RiverTile::step(){
  return;
}
RiverTile::RiverTile(){
  setText("River\n----\nDon't get your feet wet!");
  setCharacter(ACS_CKBOARD | COLOR_PAIR(2));
}
