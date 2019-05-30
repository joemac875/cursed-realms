#ifndef OPTION_H
#define OPTION_H
#include "tile.h"
#include <vector>
#include <sstream>
#include <curses.h>
class BuildOption;

class OptionManager{
  public:
    OptionManager();
    OptionManager(TileManager &tm, int height, int width, int start_y, int start_x);
    void showOptions(BuildingType acceptedBuildings, int y, int x);
    void chooseOption(int index, int y, int x);
  private:
    vector<int> availableOptions;
    vector<BuildOption *> buildOptions;
    WINDOW * optionWindow;


};

class BuildOption {
  public:
    BuildOption(TileManager &tm, BuildingType bt);
    void choose(int y, int x);
    void setText(string text);
    string getText();
    BuildingType getActivation();
  private:
    BuildingType activation;
    TileManager tileManager;
    string text;

};


#endif
