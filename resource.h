#ifndef RESOURCE_H
#define RESOURCE_H
#include <curses.h>


class ResourceManager
{
  public:
    ResourceManager();
    ResourceManager(int height, int width, int start_y, int start_x);
    void render();
    void step();
    //void refresh(const char *str);
  private:
    WINDOW * resourceWindow;
    char buffer [128];
    int wood;
};



#endif
