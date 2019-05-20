#include "building.h"

BuildingManager::BuildingManager(){
  for (int i = 0; i < MAP_HEIGHT; i++){
    vector<Building*> temp(MAP_WIDTH);
    buildingVector.push_back(temp);
  }
  buildingVector[4][5] = (new LumberMill(4,5));
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
const char * BuildingManager::getToolText (int y, int x) const{
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

void Building::setCharacter(chtype target) {
  character = target;
}
const char * Building::getToolText() const{
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

void LumberMill::step(){

}
