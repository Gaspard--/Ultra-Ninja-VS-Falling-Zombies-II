#include "Slash.hpp"

Slash::Slash(Vect<2, double> const& pos,
	     Vect<2, double> const& speed,
	     int damage = 2)
  : Weapon(pos, speed, 0.1, damage, 10),
    animationFrame(0), maxFrame(lifetime)
{
}

void Slash::update()
{
  animationFrame = spriteSheetSize - (maxFrame - lifetime) / (maxFrame / spriteSheetSize);
}

int Slash::getAnimationFrame() const
{
  return animationFrame;
}
