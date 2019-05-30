#include <curses.h>
#include <chrono>
#include <stdlib.h>

#include "manager.h"


Manager::Manager(){
  start = chrono::steady_clock::now();



  refresh();
  WINDOW * titleWindow = newwin(1, GAME_WIDTH, 0, 0);
  waddstr(titleWindow, "Cursed Realms v0.1");
  wrefresh(titleWindow);
  mainWindow = newwin(GAME_HEIGHT, GAME_WIDTH, 1, 0);
  toolTip = ToolTip(TOOLTIP_HEIGHT, 45, 1,GAME_WIDTH+2);
  resourceManager = ResourceManager(RESOURCES_HEIGHT, 45, 1+TOOLTIP_HEIGHT,GAME_WIDTH+2);
  TileManager interimTM = map.getTileManager();
  optionManager = OptionManager(interimTM, OPTIONS_HEIGHT, 45, 1+RESOURCES_HEIGHT+TOOLTIP_HEIGHT,GAME_WIDTH+2);
  keypad(mainWindow, TRUE);
  for (int i = 0; i < GAME_HEIGHT; i++){
    vector<chtype> temp(GAME_WIDTH);
    for (int j = 0; j < GAME_WIDTH; j++){
        temp[j] = '0';
    }
    charStorage.push_back(temp);
  }
}
void Manager::step(){
  getyx(mainWindow, cursor_y, cursor_x);

  map.stepAll();
  toolTip.refresh(map.getToolText(cursor_y,cursor_x));
  resourceManager.step();
  BuildingType buildOptions = map.getAcceptedBuildings(cursor_y, cursor_x);

  optionManager.showOptions(buildOptions, cursor_y+map.get_y_curs_off(), cursor_x+map.get_x_curs_off());

  wrefresh(mainWindow);
}
void Manager::render(){
  getyx(mainWindow, cursor_y, cursor_x);
  map.dumpRenders(charStorage);
  for (int i = 0; i < GAME_HEIGHT; i++){
    for (int j = 0; j < GAME_WIDTH; j++){
        mvwaddch(mainWindow, i, j, charStorage[i][j]);
    }
  }
  wmove(mainWindow, cursor_y, cursor_x);
  wrefresh(mainWindow);
}

void Manager::cursorMovement(){
  int ch = getch();
  if (ch == ERR) return;


  int x,y;
  int indexChoice = -1;
  getyx(mainWindow, y, x);
  switch(ch){

    case 'w':
      if (y==0) map.shift(0);
      wmove(mainWindow, y-1, x);
      break;
    case 'a':
      if (x==0) map.shift(3);
      wmove(mainWindow, y, x-1);
      break;
    case 's':
      if (y==GAME_HEIGHT-1) map.shift(2);
      wmove(mainWindow, y+1, x);
      break;
    case 'd':
      if (x==GAME_WIDTH-1) map.shift(1);
      wmove(mainWindow, y, x+1);

      break;
    case '1':
      indexChoice = 0;
      break;
    case '2':
      indexChoice = 1;
      break;
    case '3':
      indexChoice = 2;
      break;
    case '4':
      indexChoice = 3;
      break;
    default:
      break;
  }

  getyx(mainWindow, y, x);

  if (indexChoice != -1){
    optionManager.chooseOption(indexChoice, cursor_y+map.get_y_curs_off(), cursor_x+map.get_x_curs_off());
  }
  BuildingType buildOptions = map.getAcceptedBuildings(y, x);
  optionManager.showOptions(buildOptions, y+map.get_y_curs_off(), x + map.get_x_curs_off());
  resourceManager.refresh();
  toolTip.refresh(map.getToolText(y,x));
  wrefresh(mainWindow);

}
void Manager::mainLoop(){
  while(1){
    // check to see if we can step up the game
    double elapse = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
    if (elapse > TURN_TIME){
        start = chrono::steady_clock::now();
        step();
    }
    // check to see if user pressed anything
    render();
    cursorMovement();
  }
}
