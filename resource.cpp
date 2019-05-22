#include "resource.h"


int ResourceManager::currentWood;
ResourceManager::ResourceManager(int height, int width, int start_y, int start_x){
  resourceWindow = newwin(height, width, start_y, start_x);
  keypad(resourceWindow, TRUE);
  box(resourceWindow,0,0);
  wrefresh(resourceWindow);


}
ResourceManager::ResourceManager(){}

void ResourceManager::step(){
  render();
}
void ResourceManager::addWood(int amount){
  currentWood += amount;
}




void ResourceManager::render(){
  werase(resourceWindow);

  sprintf (buffer, "Resources\nWood: %d", currentWood);
  mvwaddstr(resourceWindow, 0, 0, buffer);
  wrefresh(resourceWindow);
}
