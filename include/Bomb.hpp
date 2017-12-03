#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

struct Bomb : public Weapon
{
  bool explodes;

  Bomb(Vect<2, double> const& pos,
       Vect<2, double> const& speed,
       int damage);
  ~Bomb() = default;
};
