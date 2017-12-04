#include "Explosion.hpp"

Explosion::Explosion(Vect<2, double> const& pos,
		     double radius,
		     int damage)
  : Weapon(pos, {0.0, 0.0}, radius, damage, 20)
{
}

void Explosion::updateAnimation()
{
  //TODO
}
