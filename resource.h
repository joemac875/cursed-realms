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

    static void addWood(int amount);
    static int currentWood;
    // The bit masks for the different resources
    static int const WOOD = 1;
    static int const ANOTHER_RESOURCE = 1<<1;
    static int const ANOTHER_RESOURCE_AGAIN = 1<<2;
  private:
    WINDOW * resourceWindow;

    char buffer [128];

};



#endif
