#pragma once

#define HOUSE_SPAWN_CD 100
#define HOUSE_SPAWN_RATE 2 // Spawn rate (x / 100)
#define MAP_SIZE 100

#include <array>
#include <iostream>
#include "CityBlock.hpp"

class Logic;

class CityMap
{
  std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> cityMap;
  int cooldown;

public:
  CityMap(Logic &logic);
  ~CityMap() = default;

  void tick(Logic &logic);
  std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const &getCityMap() const;
  void printMap() const;
};
