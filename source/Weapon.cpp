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

void Weapon::hit(Mob &mob)
{
  if (mob.getLife() > 0)
    mob.setLife(mob.getLife() - damage);
}

void Weapon::update()
{
  lifetime -= 1;
}
