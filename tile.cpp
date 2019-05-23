#include "tile.h"

vector<vector<TerrainTile* > > TileManager::tileVector;

TileManager::TileManager(){
  noiseGen.SetNoiseType(FastNoise::Simplex);
  noiseGen.SetFrequency(.125);
  noiseGen.SetSeed(time(NULL));
  for (int i = 0; i < MAP_HEIGHT; i++){
    vector<TerrainTile* > temp(MAP_WIDTH);
    for (int j = 0; j < MAP_WIDTH; j++){
        double x = noiseGen.GetNoise(i,j);
        if (x < 0.0) temp[j]= new PlainsTile(i, j);
        else temp[j] = new ForestTile(i, j);
        // Set the height of the tile to be something random
        noiseGen.SetFrequency(.05);
        temp[j]->setHeight(noiseGen.GetNoise(i,j));
        noiseGen.SetFrequency(.15);
    }
    tileVector.push_back(temp);
  }
  createRivers(10);
  addBuilding <LumberMill> (5,5);
}
void TileManager::createRivers(int chunkSize){
  // go through in chunks of
  for (int i = chunkSize / 2; i < MAP_HEIGHT; i += chunkSize){
    for (int j = chunkSize / 2; j < MAP_WIDTH; j += chunkSize){
        // higher places have a higher chance of getting a river
        double augRiverProg  = baseRiverProb * tileVector[i][j]->getHeight();
        double roll = ((double) rand() / (RAND_MAX));
        if (roll < augRiverProg){
          delete tileVector[i][j];
          tileVector[i][j] = new RiverTile(i, j);
          fillRiver(i, j);
        }
    }
  }
}
void TileManager::fillRiver(int y, int x){
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
  tileVector[min_y][min_x] = new RiverTile(min_y, min_x);
  fillRiver(min_y, min_x);
}
void TileManager::dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset){
  for (int i = 0; i < storage.size(); i++){
    for (int j = 0; j < storage[i].size(); j++){
        storage[i][j] = tileVector[i+y_offset][j+x_offset]->render();
    }
  }
}
void TileManager::stepAll(){
  for (int i = 0; i < MAP_HEIGHT; i++){
    for (int j = 0; j < MAP_WIDTH; j++){
        tileVector[i][j]->step();
    }
  }
}
string TileManager::getToolText(int y, int x){
  return tileVector[y][x]->getToolText();
}
//ToDo - Implement destructor for terrain manager

////////////////////////////////////////////////////////
Tile::~Tile(){
}
Tile::Tile(){}

chtype Tile::render(){
  return character;
}
int Tile::getX() const{
  return x_coord;
}
int Tile::getY() const{
  return y_coord;
}
void Tile::setX(int x){
  x_coord = x;
}
void Tile::setY(int y){
  y_coord = y;
}
void Tile::setCharacter(chtype target){
  character = target;
}
void Tile::setText(string target){
  description  = target;
}
string Tile::getToolText()  {
  return description;
}
void Tile::setHeight(double target){
  height = target;
}
double Tile::getHeight() const {
  return height;
}
////////////////////////////////////////////////////////
TerrainTile::TerrainTile(int y, int x){
  setY(y);
  setX(x);
}
int TerrainTile::getUsability(){
  return usability;
}

chtype TerrainTile::render(){
  if (building == nullptr){
    return character;
  };
  return building->render();
}
string TerrainTile::getToolText()  {
  if (building == nullptr){
    return description;
  };
  return building->getToolText();
}
void TerrainTile::setBuilding(BuildingTile * tile){
  building = tile;
}
void TerrainTile::step(){
  if (building == nullptr){
    return;
  };
  building->step();
}
////////////////////////////////////////////////////////

PlainsTile::PlainsTile(int y, int x) : TerrainTile(y, x){
  setText("Plains\n----\nA wholly uninspiring terrain tile.");
  setCharacter(' ');
}


ForestTile::ForestTile(int y, int x) : TerrainTile(y, x){
  usability = ResourceManager::WOOD;
  setText("Forest\n----\nLush trees veil the ultimate resource.");
  setCharacter(ACS_DIAMOND | COLOR_PAIR(1));
}


RiverTile::RiverTile(int y, int x) : TerrainTile(y, x){
  setText("River\n----\nDon't get your feet wet!");
  setCharacter(ACS_CKBOARD | COLOR_PAIR(2));
}
////////////////////////////////////
BuildingTile::BuildingTile(int y, int x){
  setY(y);
  setX(x);
};

////////////
LumberMill::LumberMill(int y, int x) : BuildingTile(y, x){
  setText("Lumber Mill\n----\nOwee this makes wood.");
  setCharacter('L');
  production = 0;
}
int LumberMill::calculateProduction(int acceptedUsage){
  int prod = 0;

  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if ((i!=0) || (j !=0)){
          int use = TileManager::tileVector[i+getY()][j+getY()]->getUsability();
          if (use & acceptedUsage) prod +=1;


      }
    }
  }
  return prod;
}
void LumberMill::setProduction(int target){
  production = target;
}
string LumberMill::getToolText(){
  //for now jsut
  return description + "\nProduction: " + to_string(production);
}
void LumberMill::step(){
  setProduction(calculateProduction(ResourceManager::WOOD));
  ResourceManager::addWood(production);

}
