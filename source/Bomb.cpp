#include "Bomb.hpp"

Bomb::Bomb(Vect<2, double> const& pos,
	   Vect<2, double> const& speed,
	   int damage = 0)
  : Weapon(pos, speed, 0.08, damage, 90),
    animationFrame(0), maxFrame(lifetime), frameRatio(maxFrame / spriteSheetSize),
    explodes(false)
{
}

void Bomb::updateAnimation()
{
  animationFrame = (maxFrame - lifetime) / frameRatio;
}

float Bomb::getAnimationFrame() const
{
  return static_cast<float>(animationFrame < spriteSheetSize ? animationFrame : spriteSheetSize - 1);
}
