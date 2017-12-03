#include "Weapon.hpp"

Weapon::Weapon(Vect<2, double> const& pos,
	       Vect<2, double> const& speed,
	       double radius,
	       int damage,
	       int lifetime)
  : entity({pos, speed, radius, 0.0, 0.0}),
    damage(damage),
    lifetime(lifetime)
{
}

void Weapon::hit(Zombie &zombie)
{
  if (zombie.getLife() > 0)
    zombie.setLife(zombie.getLife() - damage);
}


void Weapon::update()
{
  lifetime -= 1;
}
