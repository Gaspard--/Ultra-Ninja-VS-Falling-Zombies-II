#include "Shuriken.hpp"

Shuriken::Shuriken(Vect<2, double> const& pos,
		   Vect<2, double> const& speed,
		   int damage = 1)
  : Weapon(pos, speed, 0.05, damage, 120),
    animationFrame(0), maxFrame(lifetime),
    nbFrames(maxFrame / 20), touched(false)
{
}

void Shuriken::updateAnimation()
{
  animationFrame = (lifetime % nbFrames == 0) ? !animationFrame : animationFrame;
}

float Shuriken::getAnimationFrame() const
{
  return static_cast<float>(animationFrame);
}
