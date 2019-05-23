#ifndef TOOLTIP_H
#define TOOLTIP_H
#include <curses.h>
#include <vector>
#include <chrono>
#include "FastNoise.h"
#include <string>
#include "settings.h"
using namespace std;
class ToolTip
{
  public:
    ToolTip();
    ToolTip(int start_y, int start_x, int width, int height);
    void refresh(string str);
  private:
    WINDOW * toolTipWindow;

};

#endif
