#include "Slash.hpp"

Slash::Slash(Vect<2, double> const& pos,
	     Vect<2, double> const& speed,
	     int damage = 2)
  : Weapon(pos, speed, 0.1, damage)
{
}

Slash::~Slash()
{
}

void Slash::hit(Zombie &zombie)
{
  if (zombie.getLife() > 0)
    zombie.setLife(zombie.getLife() - damage);
}
