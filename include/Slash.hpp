#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

struct Slash : public Weapon
{
public:
  Slash(Vect<2, double> const& pos,
	Vect<2, double> const& speed,
	int damage);
  ~Slash() = default;
};
