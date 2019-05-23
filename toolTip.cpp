
#include "toolTip.h"
ToolTip::ToolTip(int height, int width, int start_y, int start_x){
  toolTipWindow = newwin(height, width, start_y, start_x);
  keypad(toolTipWindow, TRUE);
  refresh("Welcome to the cursed realm.");
  //box(toolTipWindow, 0 , 0);

}
ToolTip::ToolTip(){

}

void ToolTip::refresh(string str){
  werase(toolTipWindow);

  mvwaddstr(toolTipWindow, 0, 0, str.c_str());
  wrefresh(toolTipWindow);
}
