#pragma once

#include "Zombie.hpp"

struct Weapon
{
  Weapon(Vect<2, double> const& pos,
	 Vect<2, double> const& speed,
	 double radius,
	 int damage,
	 int lifetime);
  ~Weapon() = default;

  void update();
  void hit(Zombie &zombie);

  Entity entity;
  int damage;
  int lifetime;
};
