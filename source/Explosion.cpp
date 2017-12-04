#include "Explosion.hpp"

Explosion::Explosion(Vect<2, double> const& pos,
		     double radius,
		     int damage)
  : Weapon(pos, {0.0, 0.0}, radius, damage, 40),
    animationFrame(0), maxFrame(lifetime), frameRatio(maxFrame / spriteSheetSize)
{
}

void Explosion::updateAnimation()
{
  animationFrame = (maxFrame - lifetime) / frameRatio;
}

float Explosion::getAnimationFrame() const
{
  return static_cast<float>(animationFrame < spriteSheetSize ? animationFrame : spriteSheetSize - 1);
}
