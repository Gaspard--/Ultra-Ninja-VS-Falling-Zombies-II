#pragma once

#include <vector>
#include "Weapon.hpp"
#include "Slash.hpp"
#include "Explosion.hpp"
#include "Bomb.hpp"

struct WeaponManager
{
  std::vector<Slash> slashes;
  std::vector<Bomb> bombs;
  std::vector<Explosion> explosions;

  WeaponManager();
  ~WeaponManager() = default;

  void update();
};
