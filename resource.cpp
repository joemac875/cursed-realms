#include "resource.h"

ResourceManager::ResourceManager(int height, int width, int start_y, int start_x){
  resourceWindow = newwin(height, width, start_y, start_x);
  keypad(resourceWindow, TRUE);
  box(resourceWindow,0,0);
  wrefresh(resourceWindow);
  wood = 5;
}
ResourceManager::ResourceManager(){}

void ResourceManager::step(){
  render();
}

void ResourceManager::render(){
  werase(resourceWindow);
  sprintf (buffer, "Resources\nWood: %d", wood--);
  mvwaddstr(resourceWindow, 0, 0, buffer);
  wrefresh(resourceWindow);
}
