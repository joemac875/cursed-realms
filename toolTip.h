#ifndef TOOLTIP_H
#define TOOLTIP_H

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
