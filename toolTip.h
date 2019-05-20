#ifndef TOOLTIP_H
#define TOOLTIP_H
#include <curses.h>
#include <vector>
#include <chrono>
#include "FastNoise.h"
#include "terrain.h"
#include "settings.h"
class ToolTip
{
  public:
    ToolTip();
    ToolTip(int start_y, int start_x, int width, int height);
    void refresh(const char *str);
  private:
    WINDOW * toolTipWindow;
};

#endif
