#include "Slash.hpp"

Slash::Slash(Vect<2, double> const& pos,
	     Vect<2, double> const& speed,
	     int damage = 2)
  : Weapon(pos, speed, 0.1, damage, 20),
    animationFrame(0), maxFrame(lifetime), frameRatio(maxFrame / spriteSheetSize)
{
}

void Slash::updateAnimation()
{
  animationFrame = (maxFrame - lifetime) / frameRatio;
}

float Slash::getAnimationFrame() const
{
  return static_cast<float>(animationFrame < spriteSheetSize ? animationFrame : spriteSheetSize - 1);
}
