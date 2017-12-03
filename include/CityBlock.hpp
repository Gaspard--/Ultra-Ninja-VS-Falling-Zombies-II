#pragma once

#define REPOP_HAB_CD 500

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
  void tick(/*Logic &logic*/);
  bool upgrade();
};
