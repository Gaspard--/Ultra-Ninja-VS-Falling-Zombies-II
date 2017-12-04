#include <cmath>
#include "Slash.hpp"

Slash::Slash(Vect<2, double> const& pos,
	     Vect<2, double> const& speed,
	     int damage = 2, int nbLaunch)
  : Weapon(pos, speed, 0.1, damage, 20),
    animationFrame(0),
    maxFrame(lifetime),
    frameRatio(maxFrame / spriteSheetSize),
    nbLaunch(nbLaunch)
{
  if (std::abs(entity.fixture.speed[0]) > std::abs(entity.fixture.speed[1]))
    {
      horizontal = true;
      reversed = entity.fixture.speed[0] > 0.0;
    }
  else
    {
      horizontal = false;
      reversed = entity.fixture.speed[1] > 0.0;
    }
}

void Slash::updateAnimation()
{
  animationFrame = (maxFrame - lifetime) / frameRatio;
}

float Slash::getAnimationFrame() const
{
  return static_cast<float>(animationFrame < spriteSheetSize ? animationFrame : spriteSheetSize - 1);
}

int Slash::getNbLaunch() const
{
  return nbLaunch;
}

bool Slash::isHorizontal() const
{
  return horizontal;
}

bool Slash::isReversed() const
{
  return reversed;
}
