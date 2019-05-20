#include <curses.h>
#include <chrono>
#include <stdlib.h>

#include "manager.h"


Manager::Manager(){
  start = chrono::steady_clock::now();
  map = Map();
  refresh();
  WINDOW * titleWindow = newwin(2, GAME_WIDTH, 0, 0);
  waddstr(titleWindow, "Cursed Realms v0.1");
  wrefresh(titleWindow);
  mainWindow = newwin(GAME_HEIGHT, GAME_WIDTH, 2, 0);
  toolTip = ToolTip(GAME_HEIGHT/2, 30, 1,GAME_WIDTH+2);
  resourceManager = ResourceManager(GAME_HEIGHT/2, 30, 1+GAME_HEIGHT/2,GAME_WIDTH+2);
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
  //getyx(mainWindow, cursor_y, cursor_x);
  map.stepAll();
  resourceManager.step();
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
    default:
      break;
  }
  getyx(mainWindow, y, x);
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
