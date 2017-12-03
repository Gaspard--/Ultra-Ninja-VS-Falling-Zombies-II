#pragma once

#include <vector>
#include "Weapon.hpp"

struct WeaponManager
{
public:
  WeaponManager();
  ~WeaponManager() = default;

  std::vector<Slash> slashes;
  std::vector<Bomb> bombs;
};
