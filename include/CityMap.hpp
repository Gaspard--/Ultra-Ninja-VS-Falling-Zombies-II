#pragma once

// Spawn rate / 100
#define HOUSE_SPAWN_RATE 20
#define MAP_SIZE 100

#include <array>
#include "CityBlock.hpp"

class CityMap
{
  std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> cityMap;
  int cooldown;

public:
  CityMap();
  ~CityMap() = default;

  void tick(/*Logic &logic*/);
  std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const &getCityMap() const;
};
