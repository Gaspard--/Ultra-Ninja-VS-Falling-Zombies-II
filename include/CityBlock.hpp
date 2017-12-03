#pragma once

#define REPOP_HAB_CD 1000

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
  BlockType type;

public:
  int x;
  int y;

  CityBlock();
  ~CityBlock() = default;

public:
  void tick(/*Logic &logic*/);
  bool upgrade();
  BlockType getType() const;
};
