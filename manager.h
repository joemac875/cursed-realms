#ifndef MANAGER_H // include guard
#define MANAGER_H
#include "toolTip.h"
#include "map.h"
#include "settings.h"
#include "resource.h"
// millis that a step takes
#define TURN_TIME 1500
using namespace std;
class Manager
{
  public:
    // Constructor
    Manager();
    /*
    Representative of one ingame time step.
    @param none
    @return none
    */
    void step();
    /*
    The main loop that executes while the game is running
    @param none
    @return null
    */
    void mainLoop();
    /*
    Tries to get user input from the player.
    @param none
    @return null
    */
    void cursorMovement();
    void render();
    vector<vector<chtype> > charStorage;
  private:
    WINDOW * mainWindow;
    chrono::steady_clock::time_point start;
    int cursor_x;
    int cursor_y;
    ToolTip toolTip;
    Map map;
    ResourceManager resourceManager;
};

#endif
