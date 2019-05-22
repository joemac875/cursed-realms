#include "building.h"
using namespace std;
BuildingManager::BuildingManager(){
  for (int i = 0; i < MAP_HEIGHT; i++){
    vector<Building*> temp(MAP_WIDTH);
    buildingVector.push_back(temp);
  }

}
void BuildingManager::stepAll(){
  for (int i = 0; i < MAP_HEIGHT; i++){
    for (int j = 0; j < MAP_WIDTH; j++){
      if (buildingVector[i][j] != 0){
          buildingVector[i][j]->step();
      }
    }
  }
}
void BuildingManager::dumpRenders(vector<vector<chtype> > &storage, int y_offset, int x_offset){
  for (int i = 0; i < storage.size(); i++){
    for (int j = 0; j < storage[i].size(); j++){
        if(buildingVector[i+y_offset][j+x_offset] != 0) {
          storage[i][j] = buildingVector[i+y_offset][j+x_offset]->render();
        }
    }
  }
}
string BuildingManager::getToolText (int y, int x) const{
  if (buildingVector[y][x] == 0) return 0;
  return buildingVector[y][x]->getToolText();
}
Building::Building(){

}
Building::Building(int y, int x){
  x_coord = x;
  y_coord = y;

}


void Building::setText(const char * target) {
  text = target;
}
int Building::getProduction() const{
  return production;
}
void Building::setProduction(int target){
  production = target;
}
void Building::setCharacter(chtype target) {
  character = target;
}
const char * Building::getDescription() const{
  return text;
}
chtype Building::render() {
  return character;
}
int Building::getX(){
  return x_coord;
}
int Building::getY(){
  return y_coord;
}

LumberMill::LumberMill(int y, int x) : Building(y,x){
  setText("Lumbermill\n----\nProduces lumber. The more neighboring trees the better!");
  setCharacter('L');
}
string LumberMill::getToolText(){
  string x;
  x = "HELLO";
  return x;
}
int LumberMill::calculateProduction(int acceptedUsage){
  int prod = 0;
  int y = getY();
  int x = getX();
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if ((i != 0) || (j != 0))
        if (TerrainManager::tileVector[y + i][x + j]->getUsability() & acceptedUsage){
            prod++;
        }
    }
  }
  return prod;
}
void LumberMill::step(){
  setProduction(calculateProduction(ResourceManager::WOOD));
  ResourceManager::addWood(getProduction());
  return;
}
