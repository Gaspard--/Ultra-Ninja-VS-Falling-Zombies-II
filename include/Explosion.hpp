#pragma once

# include "Weapon.hpp"

class Explosion : public Weapon
{
private:
  int animationFrame;
  int maxFrame;
  static constexpr int spriteSheetSize = 4;
  int frameRatio;

public:
  Explosion(Vect<2, double> const& pos,
	    double radius,
	    int damage);

  void updateAnimation();
  float getAnimationFrame() const;
};
