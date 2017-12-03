#include "Shuriken.hpp"

Shuriken::Shuriken(Vect<2, double> const& pos,
		   Vect<2, double> const& speed,
		   int damage = 1)
  : Weapon(pos, speed, 0.01, damage, 60),
    touched(false)
{
}

void Shuriken::updateAnimation()
{
  //TODO
}
