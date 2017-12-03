#pragma once

#include <vector>
#include <algorithm>
#include "Weapon.hpp"
#include "Slash.hpp"
#include "Explosion.hpp"
#include "Bomb.hpp"
#include "Shuriken.hpp"

struct WeaponManager
{
  std::vector<Slash> slashes;
  std::vector<Bomb> bombs;
  std::vector<Explosion> explosions;
  std::vector<Shuriken> shurikens;

  WeaponManager();
  ~WeaponManager() = default;

  void update();
};
