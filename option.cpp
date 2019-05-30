#include "option.h"

OptionManager::OptionManager(){
}
OptionManager::OptionManager(TileManager &tm, int height, int width, int start_y, int start_x){

  optionWindow = newwin(height, width, start_y, start_x);
  keypad(optionWindow, TRUE);
  box(optionWindow, 0 , 0);
  wrefresh(optionWindow);
  ostringstream optionDesc;
  buildOptions.push_back(new BuildOption(tm, BT_LumberMill));
  optionDesc << "Lumber mill" << endl << "\tCosts 25 wood" << endl;
  buildOptions[0]->setText(optionDesc.str());
  optionDesc.str("");
  optionDesc.clear();
  buildOptions.push_back(new BuildOption(tm, BT_Road));
  optionDesc << "Road" << endl << "\tCosts 10 wood"<<endl;
  buildOptions[1]->setText(optionDesc.str());
  optionDesc.str("");
  optionDesc.clear();
  buildOptions.push_back(new BuildOption(tm, BT_Bridge));
  optionDesc << "Bridge" << endl << "\tCosts 20 wood"<<endl;
  buildOptions[2]->setText(optionDesc.str());
  optionDesc.str("");
  optionDesc.clear();
  buildOptions.push_back(new BuildOption(tm, BT_House));
  optionDesc << "House" << endl << "\tCosts 40 wood"<<endl;
  buildOptions[3]->setText(optionDesc.str());
  optionDesc.str("");
  optionDesc.clear();
  buildOptions.push_back(new BuildOption(tm, BT_Farm));
  optionDesc << "Farm" << endl << "\tCosts 15 wood"<<endl;
  buildOptions[4]->setText(optionDesc.str());
}
void OptionManager::showOptions(BuildingType acceptedBuildings, int y, int x){
  availableOptions.clear();
  string optionString = "-Build Options-\n";
  int counter = 1;
  for (int i = 0; i < buildOptions.size(); i++){
    if ((acceptedBuildings & buildOptions[i]->getActivation()) && TileManager::pathToKeep(y,x)){
      optionString += to_string(counter++) + ") ";
      optionString += buildOptions[i]->getText();
      availableOptions.push_back(i);
    }
  }
  werase(optionWindow);
  mvwaddstr(optionWindow, 0, 0, optionString.c_str());
  wrefresh(optionWindow);
}
void OptionManager::chooseOption(int index, int y, int x){
  if (index >= availableOptions.size()) return;
  buildOptions[availableOptions[index]]->choose(y,x);
}

BuildOption::BuildOption(TileManager &tm, BuildingType bt){
  tileManager = tm;
  activation = bt;
}
void BuildOption::choose(int y, int x){
  tileManager.create(activation,y,x);
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
