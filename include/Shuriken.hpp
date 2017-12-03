#pragma once

#include "Weapon.hpp"

struct Shuriken : public Weapon
{
  bool touched;

  Shuriken(Vect<2, double> const& pos,
	   Vect<2, double> const& speed,
	   int damage);
  ~Shuriken() = default;
};
