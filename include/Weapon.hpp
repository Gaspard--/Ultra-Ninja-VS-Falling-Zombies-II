#pragma once

#include "Entity.hpp"

struct Weapon
{
  Weapon(Vect<2, double> const& pos,
	 Vect<2, double> const& speed,
	 double radius,
	 int damage);
  ~Weapon() = default;

  Entity entity;
  int const damage;
};
