#include "Weapon.hpp"

Weapon::Weapon(Vect<2, double> const& pos,
	       Vect<2, double> const& speed,
	       double radius,
	       int damage)
  : entity({pos, speed, radius, 0.0, 0.0}),
    damage(damage)
{
}
