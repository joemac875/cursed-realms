#include "option.h"
string buildDescription(BuildingType bt);
OptionManager::OptionManager(){
}
void OptionManager::next(){
  currentOption = (currentOption + 1) % LAST_OPTION;
}
OptionManager::OptionManager(TileManager &tm, int height, int width, int start_y, int start_x){

  optionWindow = newwin(height, width, start_y, start_x);
  keypad(optionWindow, TRUE);
  box(optionWindow, 0 , 0);
  wrefresh(optionWindow);

  miscOptions.push_back(new RmBuildingOption(tm));
  miscOptions.push_back(new PlaceKeepOption(tm));
  for (int i=0; i<buildables.size();i++){
    buildOptions.push_back(new BuildOption(tm, buildables[i]));
    buildOptions[i]->setText(buildDescription(buildables[i]));
  }
}
void OptionManager::showOptions(BuildingType acceptedBuildings, int y, int x){
  availableOptions.clear();
  int counter = 1;
  string optionString = "No Options";
  if (currentOption == OT_BuildOption){
    optionString = "-Build Options- (press 'e' to see next)\n";

    for (int i = 0; i < buildOptions.size(); i++){
      if ((acceptedBuildings & buildOptions[i]->getActivation())){
        if (TileManager::pathToKeep(y,x)){
          optionString += to_string(counter++) + ") ";
          optionString += buildOptions[i]->getText();
          availableOptions.push_back(i);
        }
      }
    }
  }
  if (currentOption == OT_MiscOption){
    optionString = "-Misc Options- (press 'e' to see next)\n";
    for (int i = 0; i < miscOptions.size(); i++){
      if (miscOptions[i]->shouldShow(y,x)){
        optionString += to_string(counter++) + ") ";
        optionString += miscOptions[i]->getText();
        availableOptions.push_back(i);
      }

      }
    }

  werase(optionWindow);
  mvwaddstr(optionWindow, 0, 0, optionString.c_str());
  wrefresh(optionWindow);
}

void OptionManager::chooseOption(int index, int y, int x){
  if (index >= availableOptions.size()) return;
  if (currentOption == OT_BuildOption){
    buildOptions[availableOptions[index]]->choose(y,x);
  }
  if (currentOption == OT_MiscOption){
    miscOptions[availableOptions[index]]->choose(y,x);
  }
}

BuildOption::BuildOption(TileManager &tm, BuildingType bt){
  tileManager = tm;
  activation = bt;
}
void BuildOption::choose(int y, int x){
  tileManager.createBuilding(activation,y,x);
}
BuildingType BuildOption::getActivation(){
  return activation;
}
void BuildOption::setText(string target){
  text = target;
}
string BuildOption::getText(){
  return text;
}
/////////
MiscOption::MiscOption(TileManager &tm){
  tileManager = tm;
}
string MiscOption::getText(){ return text;};
void MiscOption::setText(string target){text = target;}
RmBuildingOption::RmBuildingOption(TileManager &tm) : MiscOption(tm){
  setText("Destroy Building\n");
}
void RmBuildingOption::choose(int y, int x){
  getTileManager().removeBuilding(y, x);
}
bool RmBuildingOption::shouldShow(int y, int x){
  if (TileManager::canRemoveBuilding(y,x)) return true;
  return false;
}

PlaceKeepOption::PlaceKeepOption(TileManager &tm) : MiscOption(tm){
  setText("Place Keep\n");
}
bool PlaceKeepOption::shouldShow(int y, int x){
  if (TileManager::keep == nullptr) return true;
  return false;
}
void PlaceKeepOption::choose(int y, int x){
  getTileManager().createBuilding(BT_Keep,y, x);
}

/////////

string buildDescription(BuildingType bt){
    if (bt == BT_Farm)
      return "Farm\n\tCost 15 wood\n";
    if (bt == BT_Road)
      return "Road\n\tCost 10 wood\n";
    if (bt == BT_LumberMill)
      return "LumberMill\n\tCost 25 wood\n";
    if (bt == BT_House)
      return "House\n\tCost 40 wood\n";
    if (bt == BT_Bridge)
      return "Bridge\n\tCost 20 wood\n";
    return "Not implemented";

}
/////////
