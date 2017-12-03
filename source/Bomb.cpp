#include "Bomb.hpp"

Bomb::Bomb(Vect<2, double> const& pos,
	   Vect<2, double> const& speed,
	   int damage = 2)
  : Weapon(pos, speed, 0.1, damage, 60)
{
}

constexpr double Bomb::explosionRadius()
{
  return 0.5;
}

void Bomb::explosion()
{
}
