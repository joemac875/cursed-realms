#include <iostream>
#include <curses.h>
#include "manager.h"
using namespace std;
int main(){
  // ncurses intialization
  srand(time(NULL));
  initscr();
  start_color();
  cbreak();
  noecho();
  init_pair(1,COLOR_GREEN,0);
  init_pair(2,COLOR_BLUE,0);
  init_pair(3,COLOR_YELLOW,0);
  init_pair(4,COLOR_MAGENTA,0);
  clear();
  nodelay(stdscr, TRUE);
  Manager gameManager = Manager();
  gameManager.step();
  gameManager.mainLoop();
  endwin();
  return 0;
}
