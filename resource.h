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
    void refresh();
    static int currentWood;
    static int currentFamily;
    static int currentFood;
    static int currentAttrition;
    // The bit masks for the different resources
    static int const WOOD = 1;
    static int const FAMILY = 2;
    static int const FOOD = 4;

  private:
    WINDOW * resourceWindow;

    char buffer [128];

};



#endif
