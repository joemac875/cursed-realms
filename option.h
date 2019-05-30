#ifndef OPTION_H
#define OPTION_H
#include "tile.h"
#include <vector>
#include <sstream>
#include <array>
#include <curses.h>
using namespace std;
class BuildOption;
class MiscOption;
enum OptionType {OT_MiscOption, OT_BuildOption, LAST_OPTION};
inline OptionType operator+(OptionType A, OptionType B){
  return static_cast<OptionType>(static_cast<int>(A) + static_cast<int>(B));
}
inline OptionType operator+(OptionType A, int B){
  return static_cast<OptionType>(static_cast<int>(A) + B);
}
inline OptionType operator%(OptionType A, OptionType B){
  return static_cast<OptionType>(static_cast<int>(A) % static_cast<int>(B));
}
class OptionManager{
  public:
    OptionManager();
    OptionManager(TileManager &tm, int height, int width, int start_y, int start_x);
    void showOptions(BuildingType acceptedBuildings, int y, int x);
    void chooseOption(int index, int y, int x);
    void next();
    void back();
  private:
    OptionType currentOption = OT_MiscOption;
    vector<int> availableOptions;
    vector<BuildOption *> buildOptions;
    vector<MiscOption * > miscOptions;
    array<BuildingType, 5>  buildables = {BT_LumberMill, BT_Farm, BT_House, BT_Road, BT_Bridge};
    WINDOW * optionWindow;
};

class MiscOption {
  public:
    MiscOption(TileManager &tm);
    virtual void choose(int y, int x) = 0;
    string getText();
    virtual bool shouldShow(int y, int x) = 0;
    void setText(string target);
    TileManager getTileManager(){ return tileManager;};
  private:
    TileManager tileManager;
    string text;
};

class RmBuildingOption : public MiscOption {
  public:
    RmBuildingOption(TileManager &tm);
    bool shouldShow(int y, int x);
    void choose(int y, int x);
};
class PlaceKeepOption : public MiscOption {
  public:
    PlaceKeepOption(TileManager &tm);
    bool shouldShow(int y, int x);
    void choose(int y, int x);
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
