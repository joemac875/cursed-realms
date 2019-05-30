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
  for (int i = 0; i < MAP_WIDTH; i++){
      delete tileVector[0][i];
      tileVector[0][i] = new BarrenTile(0,i);
  }
  for (int i = 0; i < MAP_WIDTH; i++){
      delete tileVector[MAP_HEIGHT-1][i];
      tileVector[MAP_HEIGHT-1][i] = new BarrenTile(MAP_HEIGHT-1,i);
  }
  for (int i = 0; i < MAP_HEIGHT; i++){
      delete tileVector[i][0];
      tileVector[i][0] = new BarrenTile(i,0);
  }
  for (int i = 0; i < MAP_HEIGHT; i++){
      delete tileVector[i][MAP_WIDTH-1];
      tileVector[i][MAP_WIDTH-1] = new BarrenTile(i,MAP_WIDTH-1);
  }

}
bool TileManager::pathToKeep(int y, int x){
  vector<bool> visitedRow(MAP_WIDTH, false);
  vector<vector<bool> > visited(MAP_HEIGHT, visitedRow);

  return pathToKeepHelper(visited, y, x);
}
bool TileManager::pathToKeepHelper(vector<vector<bool> > &visited, int y, int x){
  if (tileVector[y][x]->isRoute() == 2) return true;
  visited[y][x] = true;
  if ((y != GAME_HEIGHT-1) && tileVector[y+1][x]->isRoute()){
    if (!visited[y+1][x]){
      if (pathToKeepHelper(visited, y+1, x)) return true;
    }
  }
  if ((y != 0) && tileVector[y-1][x]->isRoute()){
    if (!visited[y-1][x]){
      if (pathToKeepHelper(visited, y-1, x)) return true;
    }
  }
  if ((x != 0) && tileVector[y][x-1]->isRoute()){
    if (!visited[y][x-1]){
      if (pathToKeepHelper(visited, y, x-1)) return true;
    }
  }
  if ((x != GAME_WIDTH-1) && tileVector[y][x+1]->isRoute()){
    if (!visited[y][x+1]){
      if (pathToKeepHelper(visited, y, x+1)) return true;
    }
  }
  return false;

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
void Tile::step(){}
////////////////////////////////////////////////////////
TerrainTile::TerrainTile(int y, int x){
  setY(y);
  setX(x);
}
int TerrainTile::getUsability(){
  if (!(building == 0)) return 0;
  return usability;
}
int TerrainTile::isRoute(){
  if (building == nullptr){
    return false;
  };
  return building->isRoute();
}
chtype TerrainTile::render(){
  if (building == nullptr){
    return character;;
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
BuildingType TerrainTile::getAcceptedBuildings(){
  if (hasBuilding()) return BT_None;
  return acceptedBuildings;
}
bool TerrainTile::hasBuilding(){
  if (building == nullptr) return false;
  return true;
}
////////////////////////////////////////////////////////
////////////
BarrenTile::BarrenTile(int y, int x) : TerrainTile(y,x){
  setText("Map Edge\n----\nA barren wasteland");
  setCharacter(ACS_HLINE | COLOR_PAIR(3));
  acceptedBuildings = BT_None;
}
PlainsTile::PlainsTile(int y, int x) : TerrainTile(y, x){
  usability = ResourceManager::FOOD;
  setText("Plains\n----\nA wholly uninspiring terrain tile.");
  acceptedBuildings = BT_LumberMill | BT_Road | BT_Keep | BT_House | BT_Farm;
  setCharacter(' ');
}
ForestTile::ForestTile(int y, int x) : TerrainTile(y, x){
  usability = ResourceManager::WOOD;
  acceptedBuildings = BT_None;
  setText("Forest\n----\nLush trees veil the ultimate resource.");
  setCharacter(ACS_DIAMOND | COLOR_PAIR(1));
}
RiverTile::RiverTile(int y, int x) : TerrainTile(y, x){
  setText("River\n----\nDon't get your feet wet!");
  acceptedBuildings = BT_Bridge;
  setCharacter(ACS_CKBOARD | COLOR_PAIR(2));
}
////////////////////////////////////
BuildingTile::BuildingTile(int y, int x){
  setY(y);
  setX(x);
}
void BuildingTile::subtractCosts(){
  ResourceManager::currentWood -= woodCost;
  ResourceManager::currentFamily -= familyCost;
}
int BuildingTile::isRoute(){
  return false;
}
void BuildingTile::step(){
  if (turnsToBuild > 0){
    turnsToBuild--;
    return;
  }
}
bool BuildingTile::canAfford(){
  if (ResourceManager::currentWood < woodCost) return false;
  if (ResourceManager::currentFamily < familyCost) return false;
  return true;
}

chtype BuildingTile::render(){
  if (turnsToBuild > 0){
    return '0' + turnsToBuild;
  }
  return character;
}
void TileManager::create(BuildingType bt, int y, int x){
  if (bt == BT_Keep){
    tileVector[y][x]->setBuilding(new Keep(y, x));
    return;
  }
  if (!pathToKeep(y,x)) return;
  BuildingTile * embryo;
  if (bt == BT_LumberMill){
      embryo = new LumberMill(y, x);
  }
  if (bt == BT_Road){
      embryo = new Road(y, x);
  }
  if (bt == BT_Bridge){
      embryo = new Bridge(y, x);
  }
  if (bt == BT_House){
      embryo = new House(y,x);
  }
  if (bt == BT_Farm){
      embryo = new Farm(y,x);
  }
  if (embryo->canAfford()){
    tileVector[y][x]->setBuilding(embryo);
    embryo->subtractCosts();

  }
}
////////////
LumberMill::LumberMill(int y, int x) : BuildingTile(y, x){
  setText("Lumber Mill\n----\nOwee this makes wood.");
  setCharacter('L');
  woodCost   = 25;
  familyCost = 1;
  production = 0;
  turnsToBuild = 3;
}
int LumberMill::calculateProduction(int acceptedUsage){
  int prod = 0;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if ((i!=0) || (j !=0)){
          int use = TileManager::tileVector[i+getY()][j+getX()]->getUsability();
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
  if (turnsToBuild > 0){
    turnsToBuild--;
    return;
  }
  ResourceManager::currentWood += production;
}
Farm::Farm(int y, int x) : BuildingTile(y, x){
  setText("Farm\n----\nOwee this makes food.");
  setCharacter('F');
  woodCost   = 15;
  familyCost = 1;
  production = 0;
  turnsToBuild = 2;
}
int Farm::calculateProduction(int acceptedUsage){
  int prod = 0;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if ((i!=0) || (j !=0)){
          int use = TileManager::tileVector[i+getY()][j+getX()]->getUsability();
          if (use & acceptedUsage) prod +=1;
      }
    }
  }
  return prod;
}
void Farm::setProduction(int target){
  production = target;
}
string Farm::getToolText(){
  return description + "\nProduction: " + to_string(production);
}
void Farm::step(){
  setProduction(calculateProduction(ResourceManager::FOOD));
  if (turnsToBuild > 0){
    turnsToBuild--;
    return;
  }
  ResourceManager::currentFood += production;
}
Road::Road(int y, int x) : BuildingTile(y, x){
  setText("Road\n----\nAll roads lead to Rome.");
  setCharacter(ACS_BULLET | COLOR_PAIR(4));
  woodCost = 10;
  turnsToBuild = 0;
}
int Road::isRoute(){
  return 1;
}
Bridge::Bridge(int y, int x) : BuildingTile(y, x){
  setText("Bridge\n----\nAll bridges lead to Carthage.");
  setCharacter(ACS_BULLET | COLOR_PAIR(2));
  woodCost = 20;
  turnsToBuild = 0;
}
int Bridge::isRoute(){
  return 1;
}

House::House(int y, int x): BuildingTile(y, x){
  setText("House\n----\nA complex structure that holds a family.");
  setCharacter('h' | COLOR_PAIR(4));
  woodCost = 40;
  turnsToBuild = 4;
}
void House::step(){
  if (turnsToBuild > 0){
    turnsToBuild--;
    if (turnsToBuild == 0){
      ResourceManager::currentFamily ++;
      ResourceManager::currentAttrition ++;
    }
    return;
  }

}
//////
Keep::Keep(int y, int x) : BuildingTile(y, x){
  setText("Keep\n----\nBuild off this and connected roads.");
  setCharacter('H');
}
string Keep::getToolText(){
  return description;
}
void Keep::step(){
}
int Keep::isRoute(){
  return 2;
}
