#include "Bomb.hpp"

Bomb::Bomb(Vect<2, double> const& pos,
	   Vect<2, double> const& speed,
	   int damage = 0)
  : Weapon(pos, speed, 0.1, damage, 60),
    explodes(false)
{
}

void Bomb::updateAnimation()
{
  //TODO:
}
