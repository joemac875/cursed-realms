#include "resource.h"


int ResourceManager::currentWood;
int ResourceManager::currentFamily;
int ResourceManager::currentFood;
int ResourceManager::currentAttrition;
ResourceManager::ResourceManager(int height, int width, int start_y, int start_x){
  currentWood = 500;
  currentFamily = 2;
  currentAttrition = currentFamily;
  currentFood = 40;

  resourceWindow = newwin(height, width, start_y, start_x);
  keypad(resourceWindow, TRUE);
  box(resourceWindow,0,0);
  wrefresh(resourceWindow);
}
ResourceManager::ResourceManager(){}

void ResourceManager::step(){
  currentWood+=1;
  currentFood -= currentAttrition;
  render();
}
void ResourceManager::refresh(){
  render();
}
void ResourceManager::render(){
  werase(resourceWindow);
  sprintf (buffer, "-Resources-\n\nWood: %d | Food: %d | Family: %d\nFood Consumption %d\n",
           currentWood, currentFood, currentFamily, currentAttrition);
  mvwaddstr(resourceWindow, 0, 0, buffer);
  wrefresh(resourceWindow);
}
