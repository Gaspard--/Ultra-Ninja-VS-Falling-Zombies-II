#pragma once

#define REPOP_HAB_CD 500

class CityMap;
class Logic;

enum class BlockType : char
  {
    NONE = 0,
    SHED,
    HOUSE,
    MANSION,
    ROAD,
    BORDER
  };

class CityBlock
{
  int hab;
  int habMax;
  int cooldown;

public:
  BlockType type;
  int x;
  int y;

  CityBlock();
  ~CityBlock() = default;

public:
  void tick(CityMap const &, Logic &logic);
  bool upgrade(Logic &logic);
  bool hasNeighbors(CityMap const &, int x, int y);
  int getHab() const;
};
